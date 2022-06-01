# 排序

## 快速排序

与归并排序一样, 快排也是分治策略的典型应用. 但二者之间也有区别, 分治排序主要时间消耗在有序子向量的归并上面, 而划分子向量却不花费时间; 快排恰恰相反, 可以在O(1)时间内由子问题的解得到原问题的解, 但为了将原问题划分为子问题, 需要O(n)时间.

快速排序算法虽然能够确保，划分出来的子任务彼此独立，并且其规模总和保持渐进不变， 却不能保证两个子任务的规模大体相当. 实际上，甚至有可能极不平衡。因此，该算法并不能 保证最坏情况下的O(nlogn)时间复杂度.但在实际中由于其易于实现, 代码紧凑, 对随机输入序列的运行时间更小, 因而更受青睐.

### pivot

对任一向量区间S[lo ,hi), 对于任何 lo≤mi<hi, 以S[mi]为界, 都可分割出前后两个子向量S[lo, mi)和S(mi, hi), 若S[lo, mi)中的元素均不大于 S[mi]，且S(mi, hi)中的元素均不小于S[mi]，则元素S[mi]称作向量S的一个轴点(pivot).

若S经排序变为S', mi满足:

>a) S[mi] = S'[mi]
>
>b) S[lo, mi)和S'[lo, mi)的成员完全相同 
>
>c) S(mi, hi)和S'(mi, hi)的成员完全相同

因此, 前后子向量可以独立进行排序, 一旦完成, 则整个序列的排序就完成了.

### 算法雏形

```cpp
template <typename T>
void vector<T>:: quicksort(Rank lo, Rank hi){
  if(hi - lo < 2) return; // sorted
  Rank mi = partition(lo, hi-1);
  quicksort(lo, mi);
  quicksort(mi+1, hi);
}
```

可见, 轴点一旦确定, 则只需要以轴点为界, 递归对前后子向量进行快速排序后整体排序就完成了. **核心在于轴点构造算法partition()应如何实现, 可以到达多高的效率**

### 快速划分算法

问题1: 并不是每个向量都必然含有轴点

方法: 人为的构造一个轴点:

> 1. 需要取首元素m = S[lo]作为候选, 将其从向量中取出做备份, 腾出空间便于其他元素位置调整.
>
> 2. 不断移动lo和hi, 使其相互靠拢, 始终保证lo左侧元素不大于m, hi右侧元素不小于m.
> 3. 当lo与hi彼此重合时, 只需要将m回填至该位置, 即成为一个轴点.

Version A:

```CPP
template <typename T>
Rank vector<T>:: partition(Rank lo, Rank hi){
  swap(_elem[lo], _elem[lo+rand()%(hi-lo+1)]);
  T pivot = _elem[lo]; //random one as pivot
  while(lo < hi){
    while((lo < hi) && (pivot <= _elem[hi]))
      hi--;
    _elem[lo] = _elem[hi]; // if elem[hi] < pivot, swap to left-side
    while((lo < hi) && (pivot >= _elem[lo]))
      lo++;
    _elem[hi] = _elem[lo]; // if elem[lo] > pivot, swap to right-side
  }
  _elem[lo] = pivot;
  return lo;
}
```

时间复杂度为O(hi - lo)， 且由此实现的快速排序算法并不稳定。

虽然可以在线性时间内完成任务的划分，但 **子任务规模接近**在这里却无法保证： 子序列的长度与划分过程无关， 完全取决于候选pivot的值。

在最坏情况下：每次都选择最边边的值， 那么时间复杂度为O(n^2)，效率和冒泡排序相近

**平均运行时间**： O(1.386nlogn） 正是因为其良好的平均性能才被集成到Linux和STL中

#### 应对退化

当所有元素都重复时，算法的效果和之前的最差情况等效。因此总体运行时间必为O(n^2).对其做出改进

```CPP
template <typename T>
Rank Vector<T>:: partition(Rank lo, Rank hi){
  swap(_elem[lo],_elem[lo+rand()%(hi-lo+1)]);
  T pivot = _elem[lo];
  while(lo < hi){
    while(lo < hi){
      if (pivot < _elem[hi]) hi--;
      else{_elem[lo++]=_elem[hi]; break;}
    }
    while(lo < hi){
      if(pivot > _elem[lo]) lo++;
      else{_elem[hi--x`] = _elem[lo];break;}
    }
  }
  _elem[lo] = pivot;
  return lo;
}
```

也就是说，一旦遇到重复元素，那么向量拓展就停止，将重复元素移到另一侧。因此该版本为一个懒于拓展，勤于交换的算法。

此版本反复交换元素，算法的不稳定性更是雪上加霜。

## 选取与中位数

选取：`在任意一组可比较大小的元素中，如何找到由小到大次序为k者？`该类问题成为选取问题。若目标元素的秩为k则称为`K-选取问题`

由于中位数可以将原问题划分为大小明确且规模相当的两个子集， 故可以高效地确定中位数直接关系到分治算法能否高效实现。

### 蛮力算法

对所有元素排序得到序列S，S[n/2]即为所寻找的中位数。因此时间复杂度最低为nlogn + 2T(n/2) = nlog^2n

**挑战在于如何在避免全排序的前提下，在O(nlogn)时间内找出中位数**

### 众数

热身热身，先看看中位数问题简化的版本——众数。在任一无序向量A中，若有一半以上的元素值为m，则将m称为A的众数。**给定任一无序序列，如何判断是否存在众数且可找出？**

充要条件：**若众数存在，则必然同时也是中位数**

```CPP
template <typename T> bool majority(Vector<T> A, T& maj){
  maj = majEleCandidate(A);
  return majEleCheck(A, maj);
}
template <typename T> bool majEleCheck(Vector<T>A, T maj){
  int occurrence = 0;
  for(int i=0; i< A.size(); ++i){
    if(A[i]==maj) occurrence++;
  }
  return 2*occurrence > A.size();
}
```

即通过查找中位数算法得到`maj`,然后进行判断是否存在。**那么在提出高效地中位数查找算法前，如何解决该问题？**

**减而治之： 设P为A中长度为2m的前缀，若元素x在P中恰出现m次，则A有众数当且仅当后缀A-P有众数，且A-P的众数就是A的众数**

```cpp
template <typename T> T majEleCandidate(Vector<T> A){
  T maj;
  // 利用c记录maj与其他元素的差额
  for(int c = 0, i = 0; i < A.size(); ++i){
    if(c==0){ //每当c归零, 都意味着此时的前缀P可删除
      maj = A[i]; c=1;
    }
    else maj == A[i] ? c++ : c--; // 否则就更新差额计数器
  }
  return maj;
}
```

### 归并向量的中位数

**继续讨论中位数问题的简化版本：**

`任给有序向量S1和S2， 如何找出他们归并后所得有序向量S的中位数？`

**蛮力算法**

```CPP
template <typename T>
T trivialMedian (Vector<T>&S1, int lo1, int n1, Vector<T>& S2, int lo2, int n2){
  int hi1 = lo1 + n1;
  int hi2 = lo2 + n2;
  Vector<int> S;
  while((lo1<h1) && (lo2<h2)){
    while ( ( lo1 < hi1 ) && S1[lo1] <= S2[lo2] ) S.insert ( S1[lo1 ++] ); 
    while ( ( lo2 < hi2 ) && S2[lo2] <= S1[lo1] ) S.insert ( S2[lo2 ++] );
  }
  while(lo1 < h1) S.insert(S1[lo1++]);
  while(lo2 < h2) S.insert(S2[lo2++]);
  return S[(n1+n2)/2];
}
```

时间复杂度为O(n1+n2), 虽然效率还行， 但并没有用到两个子向量已有序的条件， 能否更快？

**减而治之**

考察S1的中位数m1 = S1[n/2]; S2的逆向中位数m2 = S2[n/2(上取整)-1] = S2[(n-1)/2], 并比较其大小

当n为奇数时，二者位置相同；n为偶数时，m2在m1前一位

> 若m1 = m2, 则在S中, 各有 n/2 和n/2(上)-1 = n-1个元素不大于和不小于他们，故m1和m2就是S的中位数
>
> 若m1 < m2, 则意味着在S中各有n/2个元素不大于和不小于他们
>
> 可见，这些元素或者不是S的中位数，或者与m1, m2同为S的中位数。无论如何，清楚这些元素后S中位数的数值不变。
>
> m2 < m1的情况类似
>
> 因此只需一次比较就可将问题规模减小一半，因此总时间复杂度为O(logn)

```cpp
template <typename T>
T median(Vector<T>& S1, int lo1, Vector<T>&S2, int lo2, int n){
  if (n < 3) return trivialMedian(S1, lo1, S2, lo2, n);
  int mi1 = lo1 + n/2; int mi2 = lo2 + (n-1)/2;
  if(S1[mi1]< S2[mi2]) return median(S1,mi1,S2,lo2,n+lo1-mi1);//中位数在S1右半边和S2左半边
  else if(S1[mi1]>S2[mi2]) return median(S1,lo1,S2,mi2,n+lo2-mi2);//中位数在S1左半边，S2右半边
  else return S1[mi1];
}
```

将代码推广至一般情况：S1和S2不等长

```cpp
template <typename T>
T median(Vector<T>&S1, int lo1, int n1, Vector<T>S2,int lo2, int n2){
  if(n1 > n2) return median(S2,lo2,n2, S1,lo1,n1); // 确保n1 <= n2
  if(n2 < 6) return trivialMedian(S1,lo1,n1,S2,lo2,n2); //1≤n1≤n2≤6
  if(2*n1 < n2) return median(S1,lo1,n1,S2,lo2+(n2-n1-1)/2,n1+2-(n2-n1)%2);
  //若二者差异悬殊，则可将长者的两翼直接截除
  int mi1 = lo1 + n1/2;
  int mi2a = lo2 + (n1-1)/2;
  int mi2b = lo2 + n2 - 1 - n1/2;
  if ( S1[mi1] > S2[mi2b] ) //S1左半、S2右半
    return median ( S1, lo1, n1 / 2 + 1, S2, mi2a, n2 - ( n1 - 1 ) / 2 ); 
  else if ( S1[mi1] < S2[mi2a] ) //S1右半、S2左半
    return median ( S1, mi1, ( n1 + 1 ) / 2, S2, lo2, n2 - n1 / 2 ); 
  else //S1保留，S2左右同时缩短
		return median ( S1, lo1, n1, S2, mi2a, n2 - ( n1 - 1 ) / 2 * 2 );
}
```

总体复杂度为O(log(min(n1, n2)))

### 优先级队列的选取

原问题的冲突是`一组元素中第k大的值包含的信息远少于经过全排序后的整个有序序列`，自然就会想到堆这个信息量相对较少的数据结构

算法1： 小顶堆，每次删除min，直到第k个元素。O(n+klogn)

算法2：任取k个元素组成大顶堆，将剩余的n-k个元素逐个插入堆中；每次插入后删除max，直到输入完成，堆顶即为目标元素。O(k+2(n-k)logk)

算法3：组成一个n-k的小顶堆和k的大顶堆。反复比较堆顶，只要小顶堆< 大顶堆，则交换，直到该条件不满足。大顶堆堆顶即为目标元素。O(n - k) + O(k) + min(k, n - k)∙2∙(O(logk + log(n - k)))

但上述算法在秩小的时候很不错，但当k=n/2时，退化为O(nlogn)

### 基于快速划分的选取

查找元素的位序k，就是其在对应的有序序列中的秩。就这一性质而言，该元素与轴点颇为相似。

**算法思路**：

> 1. 调用partition()构造向量A的轴点A[i]=x, 若i=k，则恰好为目标元素，返回
> 2. 否则k< i, 则选取的目标元素不可能在x右侧，删除
> 3. 若i<k, 则选取的目标元素不可能在x左侧，删除

```CPP
template <typename T> void quickselect(Vector<T>&A, Rank k){
  for(Rank lo = 0, hi = A.size()-1;lo<hi;){
    Rank i = lo, j = hi;
    T pivot = A[lo];
    while(i<j){//O(hi - lo + 1) = O(n)
      while ( ( i < j ) && ( pivot <= A[j] ) ) j--; A[i] = A[j];
      while ( ( i < j ) && ( A[i] <= pivot ) ) i++; A[j] = A[i];
    }
    A[i] = pivot;
    if(k <= i) hi = i-1;
    if(i <= k) lo = i+1;
  }
}
```

总体时间为O(n^2)

### K选取算法

延续quickselect的思路，提出一个最坏情况下仍为O(n)的k-选取算法

```CPP
select(A, k)
输入:规模为n的无序序列A，秩k≥0 
输出:A所对应有序序列中秩为k的元素 
{
  if (n = |A| < Q) return trivialSelect(A, k); //递归基:序列规模不大时直接使用蛮力算法
  将A均匀地划分为n/Q个子序列，各含Q个元素; //Q为一个不大的常数，其具体数值稍后给出
  各子序列分别排序，计算中位数，并将返些中位数组成一个序列; //可采用任何排序算法，比如选择排序
  通过递归调用select()，计算出中位数序列的中位数，记作M;
  根据其相对于M的大小，将A中元素分为三个子集:L(小于)、E(相等)和G(大于);
  if (|L| ≥ k) return select(L, k); 
  else if (|L| + |E| ≥ k) return M; 
  else return select(G, k - |L| - |E|);
}
```

## 希尔排序

### 递减增量策略

希尔排序将整个待排向量A等效地视作一个二维矩阵B，若原一维向量为A[0,n), 则对于任一固定的矩阵宽度w，A与B中的元素之间总有一一对应关系：

`B[i][j] = A[i+jw]`,即矩阵B同一列的元素自上而下依次对应A中以w为间隔的元素，因此w称为增量。

```CPP
// 算法框架
shellsort(A,n){
  取一个递增的增量序列: H = {w1=1, w2, w3, ..., wk,...}
  设k=max{i | wi< n}, 即wk为增量序列H中小于n的最后一项
  for(t=k; t>0;--t){
    将向量A视作以wt为宽度的矩阵Bt
    对Bt的每一列分别排序: Bt[i], i=0,1,...,wt-1
  }
}
```

可以看到，每一步迭代都从事先设定的某个整数序列中取出一项，以该项为宽度，将输入向量重新排列为对应宽度的二维矩阵，然后逐列分别排序。

因为增量为逆序取出的，所以各步迭代中矩阵宽度呈缩减趋势，直至最后w=1。矩阵每缩减一次并排序一轮，向量整体的有序性就进一步改善。当增量到1时，相当于对整个向量进行一次排序。

既然最后一轮排序等效于向量的整体排序，那么前面的那些步骤有必要吗？ 这涉及到`底层排序算法的特性`，**支持希尔排序的底层排序算法必须是输入敏感的**。随着向量有序性的不断提高，运行时间会锐减。以插入排序为例，当逆序元素间距不超过k时，仅需O(kn)的运行时间。因此，各步迭代对向量有序性的改善会累积下来，最终将整体成本控制在一个合理的范围内。

### 增量序列

既然希尔排序算法的主体已经确定，唯一可调整的就只有增量序列的设置与选用了。事实上，**不同的增量序列对插入排序以上特性的利用程度各异，整体效率也相差极大。**

1. shell序列

shell本人提出希尔排序时使用的序列

`Hshell = {1, 2, 4, 8, 16, 32, ..., 2^k, ...}`

我们将看到，使用该序列，希尔排序在最坏情况下的性能并不好，因为该序列除了首项外其余各项均被2整除，之前的步骤对于两组元素间的有序性并无建树。**因此，为改进希尔排序性能，首先必须尽可能减少不同增量因子之间的公共因子，彻底的方法就是保证其两两互素**

使用数论的一个基本结论：

`将不能由g和h组合生成出来的最大自然数记作x(g, h). 如果g和h互素，则必有x(g,h)=(g-1)(h-1)-1 = gh-g-h`

在向量S[0,n)中，若S[i]≤S[i+h]对任何0≤i≤n-h均成立，则称该向量h-有序。

在希尔排序中对应每一增量为h的迭代，都会在原向量中以h为间隔进行排序，称为h-排序

结论： `已经g-有序的向量，再经h-排序后,依然保持g-有序`

此时为(g,h)-有序， 且S必然有(mg+nh)-有序

**因此，逆序的间距必然不是gh的组合，只要gh互素，逆序对的间距就绝不大于(g-1)(h-1)**

由此可见，希尔排序过程中向量的有序性之所以会不断积累并改善，其原因可解释为，向量 中每个元素所能参与构成的逆序对持续减少，整个向量所含逆序对的总数也持续减少。与此同时， 随着逆序对的减少，底层所采用的插入排序算法的实际执行时间，也将不断减少，从而提高希尔 排序的整体效率。以下结合具体的增量序列，就此做出定量的估计。



> Papernov-Stasevic序列：Hps={1,3,7,15,31,63,...,2^k-1,...}, 最差情况下为O(n^1.5)
>
> Pratt序列：Hpratt={1,2,3,4,6,8,9,12,16,...,2^P3^q,...}至多运行O(nlog^2n)时间
>
> Sedgewick序列：Hsedgewick={1,5,19,41,109,209,505,929,2161,3905,8929,....}
>
> 各项均为:9∙4^k - 9∙2^k + 1或4^k-3∙2^k+1
>
> 算法在最坏情况下的时间复杂度为O(n4/3)，平均复杂度为O(n7/6), 且在一般场景下，该序列的综合效率最佳。



