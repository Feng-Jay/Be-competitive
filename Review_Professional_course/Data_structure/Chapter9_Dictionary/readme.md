# 词典

逻辑上的词典: 一组数据组成的集合, 其中各元素都是关键码和数据项合成的词条. map与dict的区别: map要求不同词条的关键码互异; dict允许多个词条有相同的关键码.二者统称为符号表, 不要求词条间能够根据关键码比较大小. 

以散列表为代表的符号表结构, 转而依赖数据项的数值来做逻辑查找和定位, key与value的地位等同, “循值访问”, 适用范围更广. **不再属于CBA式算法, 也不再服从CBA算法复杂度下界, 高效算法得以实现.** 

跳转表允许同时包含多个关键码雷同的词条; 散列表则不允许.

## 跳转表

vector和list各有所长: 前者便于静态查找, 但动态维护成本高; 后者便于增量式动态维护, 但只支持顺序查找. 因此前面提出了二叉搜索树, 但结构较复杂; 引入跳转表的目的是为了找到一个简便直观的方法完成该任务.  **查询和维护在平均意义下仅需O(logn)时间**

总体逻辑为: 内部按横向分层, 纵向相互耦合的多个列表组成{S0, S1, S2, ..., Sh}组成, h称为跳转表高度.

S0与Sh称为底层和顶层, 同层节点间有前驱后驱关系, 纵向也可以定义. 

**高层列表总是低层列表的子集, S0包含所有词条, Sh不含任何词条**

### 四联表

按上述约定, 跳转表内部各节点沿水平和垂直方向都可定义前驱和后继, 支持该连接方式的表叫四联表.

### 查找

算法: 
> 从顶层列表的头节点出发, 向右向下查找目标关键码k
> 在每一层, 从前向后找, 直到找到key > k
> 回退一步, 判断是否相等, 相等则返回
> 否则, 若到底层, 失败;
> 否则, 转至当前塔的下一节点.

**空间复杂度** : 根据“生长概率逐层减半”条件, 总体空间消耗的期望值应为O(n)

**时间复杂度** : search的单次纵向/横向跳转本身只需要常数时间, 故查找所需时间应取决于横向,纵向跳转的总次数. 其时间复杂度期望值不超过O(logn)

### 插入

在最底层查找到应该插入的位置, 然后随机令该新塔上长.

时间复杂度O(logn)

### 删除

在查找到该词条后, 依次删除塔顶.  时间复杂度O(logn)

## 散列表

只要**散列函数**, **散列表**, **冲突排解方案合理**, 散列技术可以在常数时间内实现词典的所有接口操作.(与词典规模无关)

### 完美散列

**散列表**

hashtable是散列表的底层逻辑, 由一系列可存放词条的单元组成. 故这些单元也称为bucket/桶单元. 各桶单元也按照逻辑次序在物理上连续排列. 常用数组来实现, 桶数组. 

**散列函数**

一组词条在hashtable内部的具体分布取决于hashing方案——事先在词条和桶地址间约定的某种映射关系(从关键码到桶地址的函数):

<center>hash(): key -> hash(key)</center>

hash()为散列函数, hash(key)为key的散列地址(即在散列表中的秩)

当可以在O(1)时间确定散列地址, 每一个桶恰好存一个学生的学籍词条, 没有重复和空余, 这样在时间和空间性能取得最优的散列称为**完美散列**. 但完美散列并不常见.

对于这样的情况: 尽管词典中实际需要保存的词条数目N远远少于可能出现的词条数目R, 但R个词条中的任何一个都有可能出现在词典中. 会导致空间利用率很低, 将非空桶的数目和桶单元总数的比值称为装填因子, 上述问题的实质就是在于散列表的装填因子太小, 导致空间利用率低.

### 散列函数设计

假定关键码均为[0, R)范围内的整数, 将词典中的词条数记作N, 散列表长度记作M, 通常有: R >> M > N

**因此, hash函数的作用可理解为, 将关键码的空间[0,R)压缩到散列的地址空间[0,M)**

**设计原则**:

> 1. 具有确定性, 词条E在散列表中的映射地址hash(E.key)必须取决于其关键码key.
> 2. 映射过程不能太复杂, 保证散列地址计算可快速完成, 从而保证查询/修改操作整体的O(1)执行时间
> 3. 所有关键码经映射后应尽量覆盖整个地址空间[0,M). hash()最好是满射.

因为R>>M, 所以hash()不可能是单射, 这就意味着**关键码不同的词条也会存在被映射到同一散列地址的情况**——称为散列冲突, 难以彻底避免. 虽然后续可以有解决方案, 但如果hash函数设计更为细致或充分, 便可尽可能降低冲突发生的概率.

**因此最重要的原则就是**
> 4. 关键码映射到各桶的概率尽量接近于1/M.

将关键码空间“均匀地”映射到散列地址空间, 从而避免极端低效的情况出现.

**随机性越强, 规律性越弱的散列函数越好**

1. 除余法

将散列表的长度M取为素数, 并将关键码key映射至key关于M整除的余数: hash(key) = key mod M

**采用除余法时必须将M选为素数, 否则关键码被映射到[0,M)范围内的均匀度将大幅降低, 发生冲突的概率将随着M所含素因子的增多而迅速加大.**

2. MAD法

以素数为表长的除余法仍有一定的问题: 从关键码到地址空间的角度来看, 依然有连续性. 比如: 关键码相邻对应的散列地址总是相邻的. 极小的关键码, 通常都映射到散列表的起始区段, 特别的“0”是一个不动点, 散列地址总是0.

为弥补这一不足, 可使用MAD法将关键码KEY映射为:

(axkey + b) mod M, 其中M仍为素数, a>0, b>0 且 a mod M ≠ 0

因为需要乘法, 加法, mod, 因此命名为MAD法

更多的散列函数:

* 从关键码key中取特定的若干位

* 平方取中法: 从key的十进制/二进制展开中取中间的若干位, 构成一个整数地址.

* 折叠法: 关键码的十进制或二进制展开分割成等宽的若干段, 取其总和作为散列地址.

* 异或法: 将关键码的二进制展开为等宽的若干段, 经异或运算得到散列地址.

通常为了保证上述函数取值落在合法散列地址里, 需要对M取模.

伪随机数法: rand(key) mod M

### 冲突及排解

冲突具有普遍性, 对于长的散列表, 只需要低的装填因子就会有较大概率发生一次冲突. 因此必须事先制定一套有效的对策, 以处理和排解时常发生的冲突:

* 多槽位法

将彼此冲突的每一组词条组织为一个小规模词典, 分别存放在他们共同对应的桶单元中. 简便的方法是: 统一将各桶细分为更小的若干单元, 每一槽位可组织为向量/列表.

针对关键码的任一操作都将转化为对一组槽位的操作: 首先定位到对应的桶单元, 并在其内部的一组槽位中, 进一步查找key.

**缺点**: 填装因子变低, 空间利用率很低.

* 独立链法

使用链表来实现各个桶单元的小词典. 优点: 独立链法可更为灵活地调整子字典的容量与规模, 降低空间消耗; 但一旦发生冲突则需要遍历整个链表, 查找成本增加.

* 公共溢出区法

在原散列表之外另设一个词典结构, 一旦在插入词条时发生冲突, 就将该词条转存到该词典中去. 就效果而言, 其相当于一个存放冲突词条的公共缓冲池.  此时的散列表是一种递归形式的散列表.

### 闭散列策略

独立链法虽然逻辑结构紧密, 但因为引入次级关联结构, 导致算法等复杂度大大增加. **依靠基本的散列表结构就地排解冲突反而是更好的选择.**: 新词条与已有词条冲突, 则只允许在散列表内部为其寻找另一空桶.

如此, 各桶并非只能存放特定的一组词条; 理论上讲, 每个桶单元都可存放任一词条. **开放定址策略**

**线性试探法**

若ht[hash(key)]已被占用, 则转而试探桶单元ht[hash(key)+1], ht[hash(key)+2]...直到发现一个空桶.

该方法组成的查找链在物理上保持一定的连贯性, 具有良好的数据局部性, 几乎没有IO操作. 尽管闭散列一定程度上增加冲突发生的可能, 但只要规模不小, 填装因子不太大, IO的降低会使得冲突影响微不足道.

惰性删除, 因为查找链默认是在物理上连续的, 如果删除了其中一个元素, 就会导致其后续元素无法被查找到. 因此采取如下策略:

每个桶设置一个标记位, 删除后设置, 表示其虽然为空, 但曾放入过元素. 但可以被插入元素.

随着填装因子的上升, 若还采用基本的懒惰删除法, 则不带懒惰删除的桶单元数目必将持续减少. 导致查询成本进一步攀升. 经过实验和分析, 对闭散列策略, 填装因子 < 0.5较好; 对于独立链法, 填装因子建议上限为0.9

### 更多闭散列策略

由于线性试探会导致聚集现象频发, 因此是否有其他策略呢?

1. 平方试探法

若在试探的过程中连续发生冲突, 则第j次试探的位置 = hash(key)+j^2.

但也会导致存在空桶但永远无法到达的情况, 但只要散列表长度为素数且装填因子≤0.5, 则平方试探迟早必终止于某个空桶.

2. 随机试探法

3. 再散列法

选取一个适宜的二级散列函数hash2(), 一旦在插入(key, value)时发现冲突, 则以hash2(key)作为偏移增量继续尝试,直到发现空桶.

### 散列码转换

关键码不一定就是整数类型, 所以需要一个散列码转换函数 hashcode(), 将key统一转换为一个整数.

hashcode()的要求:

1. 取值范围应覆盖系统所支持的最大整数范围

2. hashcode转换后的冲突应尽量减小.

3. hashcode转换后的数据仍与判等器保持一致

一些策略:

1. byte, short, int, char等不超过32bits的直接转换

2. longlong double之类的超过32bits的数据, 可将高32bits与低32bits分别看作两个32bits整数, 二者之和作为hashcode

3. 对于组合对象, 其中的次序有特定含义, 因此可以用多项式散列码

## 桶排序

CBA式算法对于n个整数排序, 最坏情况下要O(nlogn)时间, 实际上可以使用更低的时间完成:

hash(key) = key, 将整数视作关键码逐一插入, 然后遍历即可. 这种借助一组桶单元的分拣称为桶排序

总体运行时间为O(n+M): M为创建散列表的时间, n为关键码数量

**若输入数据允许重复, 如何高效实现排序?**

处理散列冲突即可.

在生活中常有n>>M的情况, 此时算法的复杂度为O(n), 突破了O(nlogn)的CBA算法下界.




