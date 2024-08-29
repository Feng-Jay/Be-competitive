# 排序算法

在写leetcode之前，先回顾一下已有的排序算法，这里按所需的时间复杂度进行分类:

## O(n^2) 

### 冒泡排序

该排序方式非常形象，即一轮遍历中，最大(小)的那个值会一步步地向数组尾(头)移动，非常像冒泡. 下面给出一个算法示例(在本章目录下的dummy.cpp给出了检测所有提到算法正确性的示例程序)

```C++
void bubble_sort(std::vector<int>& arr){
    int len = arr.size();
    for(int i = 0; i < len - 1; ++i){
        for (int j = 0; j < len - i - 1; ++j){
            if(arr[j] > arr[j + 1]){
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}
```

如上述过程，每次循环中，j都会从数组头开始执行如下逻辑: `如果一个数组元素大于他的后继，那就交换他们`，这样，最大的数组元素一定会在这次循环中被放在数组尾部。然后排序问题的规模从0到n-1的长度为n的数组降低到了从0到n-2的长度为n-1的数组。这也是内层循环的条件为 `j < len - i - 1`的原因。外部循环只需要执行len - 1次即可，因为此时已经找到了len - 1个最值，剩下的那个一定是最小值。

可以从算法看出，该算法遍历了n * n 次数组，因此算法的时间复杂度为 O(n^2).

但上述算法有点无脑，即外部循环一定会遍历 len - 1 次，但有些时候数据的特殊性会使得外部循环还没执行完数组就已经有序了，例如数组 `arr[7] = {1,2,3,4,9,8,6}`, 因此我们可以对冒泡算法进行一个小小的优化，即当一次循环没有执行swap时，此时整个数组已经有序了:

```C++
void opt_bubble_sort(std::vector<int>& arr){
    int len = arr.size();
    for(int i = 0; i < len - 1; ++i){
        bool swapped = false;
        for (int j = 0; j < len - i - 1; ++j){
            if(arr[j] > arr[j + 1]){
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
```

额外讨论一下, bubble_sort是稳定算法吗？(即两个元素值相同时，排序后二者的相对位置不会改变)，答案是yes，因为只有在arr[j] > arr[j + 1]时才会进行交换。

### 选择排序

如名称所示，该排序方法为每次选择一个当前数组中最小(大)的元素，然后插入数组头(尾)。

```C++
void selection_sort(std::vector<int>& arr){
    int len = arr.size();
    for(int i = 0; i < len - 1; ++i){
        int minIndex = i;
        for (int j = i + 1; j < len; ++j){
            if(arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}
```
该算法逻辑和冒泡排序类似，但不同的是选择排序通过用一个中间变量将最值记录下来，减少了程序中数据交换的次数. 还有一个不同就是选择排序不是稳定的，例如这个数组 `arr[3] = {2, 2, 1}`, 选择排序会在第一轮循环将第一个`2`与`1`进行交换，从而改变两个`2`的相对位置。

既然我们每次记录下来了minIndex，我们是否可以同时记录下maxIndex呢？该算法称为二元选择排序:

```C++
void selection_sort2(std::vector<int>& arr){
    int len = arr.size();
    for(int i = 0; i < len / 2; ++i){
        int minIndex = i;
        int maxIndex = i;
        for (int j = i + 1; j < len - i; ++j){
            if(arr[j] < arr[minIndex]){
                minIndex = j;
            }
            if(arr[j] > arr[maxIndex]){
                maxIndex = j;
            }
        }
        if (minIndex == maxIndex) break;
        std::swap(arr[minIndex], arr[i]);
        if (maxIndex == i) maxIndex = minIndex;
        std::swap(arr[maxIndex], arr[len - 1 - i]);
    }
}
```
外层的循环只需要循环 len / 2次即可: 若长度为偶数，那么所有的元素都会被挑为min/max值；若长度为奇数，那么除了剩下的一个元素，剩下的元素都已经排好序，因此整个数组也是有序的。

### 插入排序

插入排序类似打牌，维护一个有序的部分数组，然后对每个新来的元素，找到应该插入的位置:

```C++
void insertion_sort(std::vector<int>& arr){
    int len = arr.size();
    for(int i = 1; i < len; ++i){
        int j = i - 1;
        int current = arr[i];
        while(j >= 0 && current < arr[j]){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current;
    }
    printToShell(arr);
}
```

在代码中，将第一个元素视为初始有序的数组，如果current数组元素比arr[j]小，那么就移动arr[j]。当跳出循环时有两种情况: 1. j == -1, 说明current比所有数组内容都小，因此arr[0]应该被置为current；2. current >= arr[j], 此时current应该插入在arr[j + 1]的位置。二者插入位置都为j + 1.

同样我们分析其稳定性，由于判断条件是current < arr[j]时才会进行交换，因此当值相同时不会将原数组元素移动，因此是稳定的。


## O(nlog(n))

### 希尔排序

希尔排序是插入排序的一个优化，可以从排序算法的本质上来理解希尔排序: 排序的根本目的是为了消除数组中全部的逆序对，之前提到的冒泡/选择/插入排序每次交换都只能消除一组逆序对，而希尔排序通过构造增量的方式可以一次交换消除多个逆序对，以此得到时间复杂度的降低:

```C++
void shell_sort(std::vector<int>& arr){
    int len = arr.size();
    for(int gap = len/2; gap > 0; gap /= 2){
        for(int currentIndex = gap; currentIndex < len; ++ currentIndex){
            int currentNumber = arr[currentIndex];
            int prevIndex = currentIndex - gap;
            while(prevIndex >= 0 && currentNumber < arr[prevIndex]){
                arr[prevIndex + gap] = arr[prevIndex];
                prevIndex -= gap;
            }
            arr[prevIndex + gap] = currentNumber;
        }
    }
}
```
这里选择的增量是希尔在初稿论文中所用的希尔增量，即增量每次除2.

### 堆排序

可以把堆看作一个完全二叉树，在完全二叉树中，节点i的左子节点为2*i + 1, 节点i的右子节点位 2 *i + 2，最后一个非叶子节点为len/2 - 1. 大(小)顶堆的含义是节点i一定大(小)于左右子节点:

```C++
void max_heap(std::vector<int>& arr, int i, int size){
    int leftIndex = 2 * i + 1;
    int rightIndex = leftIndex + 1;
    int largestIndex = i;
    if (leftIndex < size && arr[leftIndex] > arr[largestIndex]){
        largestIndex = leftIndex;
    }
    if(rightIndex < size && arr[rightIndex] > arr[largestIndex]){
        largestIndex = rightIndex;
    }
    if(largestIndex != i){
        std::swap(arr[i], arr[largestIndex]);
        max_heap(arr, largestIndex, size);
    }
}

void build_heap(std::vector<int>& arr){
    int len = arr.size();
    for(int i = len / 2 - 1; i >= 0; --i){
        max_heap(arr, i, len);
    }
}

void heap_sort(std::vector<int>& arr){
    build_heap(arr);
    int len = arr.size();
    for(int i = len - 1; i > 0; --i){
        std::swap(arr[0], arr[i]);
        max_heap(arr, 0, i);
    }
}
```

堆排序的过程中，首先自底向上构建大顶堆，然后选择堆顶元素后放入队尾，更新大顶堆。

### 快速排序

快排的核心思想是分治，即每次选一个pivot节点，使得pivot节点左侧数值都小于该节点，右侧节点数值都大于该节点，该节点此时位置就是最后的位置。然后分别对左右侧数组进行上述过程：

```C++
int partition(std::vector<int>& arr, int begin, int end){
    int pivot = arr[begin];
    int l = begin + 1;
    int r = end;
    while(l < r){
        while(l < r && arr[l] < pivot) l++;
        while(l < r && arr[r] > pivot) r--;
        if (l != r){
            std::swap(arr[l], arr[r]);
            r--;
        }
    }
    if(l == r && arr[r] > pivot) r--;
    if(r != begin) std::swap(arr[begin], arr[r]);
    return r;
}

void quick_sort(std::vector<int>& arr, int begin, int end){
    int middle = partition(arr, begin, end);
    if (middle != begin && middle != begin + 1)
        quick_sort(arr, begin, middle - 1);
    if (middle != end && middle != end - 1)
        quick_sort(arr, middle + 1, end);
}

void quick_sort(std::vector<int>& arr){
    quick_sort(arr, 0, arr.size() - 1);
}
```

值得注意的就是`partition`函数中对特殊情况的处理，即while循环后两个特殊条件的判断


### 归并排序

我们已经很熟悉将两个有序数组合并为一个有序数组的算法了，归并排序的思想就是利用上述思想。但找到有序的数组是一个难点，冯诺依曼使用二分的方式来构造这样的有序数组:

```C++
void merge(std::vector<int>& arr, int begin, int end, std::vector<int>& result){
    int end1 = (begin + end) / 2;
    int begin2 = end1 + 1;
    int begin1 = begin;
    int end2 = end;
    int index1 = begin1;
    int index2 = begin2;
    while(index1 <= end1 && index2 <= end2){
        if(arr[index1] <= arr[index2]){
            result[index1 + index2 - begin2] = arr[index1];
            index1++;
        }else{
            result[index1 + index2 - begin2] = arr[index2];
            index2++;
        }
    }
    while (index1 <= end1) {
        result[index1 + index2 - begin2] = arr[index1];
        index1++;
    }
    while (index2 <= end2) {
        result[index1 + index2 - begin2] = arr[index2];
        index2++;
    }
    while(begin <= end){
        arr[begin] = result[begin];
        begin++;
    }
}

void merge_sort(std::vector<int>& arr, int begin, int end, std::vector<int>& result){
    if (begin == end) return;
    int middle = (begin + end) / 2;
    merge_sort(arr, begin, middle, result);
    merge_sort(arr, middle + 1, end, result);
    merge(arr, begin, end, result);
}

void merge_sort(std::vector<int>& arr){
    std::vector<int> result(arr.size(), 0);
    merge_sort(arr, 0, arr.size() - 1, result);
}
```

即递归地二分该数组，若数组长度为1则必然有序，递归过程开始出栈。