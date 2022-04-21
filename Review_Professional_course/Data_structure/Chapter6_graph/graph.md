# Graph

## Terminology

图: graph=(V, E), V中元素称作顶点, E中元素对应V中一对顶点(u,v)表示其之间某种联系. 规模 n =|V|, e = |E|

边(u, v)对应顶点u, v次序无关, 称为无向边; 若 u,v 不对等, 称为有向边. 

若E中各边均无方向, 则G称为无向图; 若E中只含有向边, 则称G为有向图; 同时包括两种, 称为混合图.
*有向图的通用性更强, 无向图和混合图均可转换为有向图*

对于任何边e = (u, v)，称顶点u和v彼此邻接(adjacent)，互为邻居;而它们都与边e 彼此关联(incident)。

在无向图中，与顶点v关联的边数，称作v的度数(degree)，记作deg(v)

有向边e = (u, v)，e称作u的出边(outgoing edge)、v的入边(incoming edge)。 v的出边总数称作其出度(out-degree)，记作outdeg(v);入边总数称作其入度(in-degree)， 记作indeg(v)。

联接于同一顶点之间的边，称作自环; 不含任何自环的图称作**简单图**

不含任何环路的有向图，称作有向**无环图(directed acyclic graph, DAG)**

经过图中各边一次且恰好一次的环路称作欧拉环路 (Eulerian tour). 其长度也恰好等于图中边的总数e。

经过图中各顶点一次且恰好一次的环路，称作哈密尔顿环路(Hamiltonian tour)，其长度亦等于构成环路的边数

## Adjacency Matrix

使用nxn方阵表示n个点构成的图的方式. 

**时间性能**

各顶点的编号可直接变为邻接矩阵的秩, 只需要 O(1)时间.(vector寻秩访问)

边的静态和动态操作也仅需要O(1)时间.(邻接矩阵的空间冗余)

但**顶点的动态操作十分耗时,为了插入顶点,顶点vector需要插入一个元素, 边集向量维度增加1,每行都要添加一个元素,且要多添加一行. 删除顶点与之类似.**

通常算法中, 顶点的动态操作远少于其他操作, 就分摊意义而言, 单次耗时不超过O(n)

**空间性能**

O(n^2), 无向图因为对称, 近一半空间冗余, 可进一步压缩, 但也不会来带数量级的差距. 

## Adjacency List

Adjacency Matrix采用vector的数据结构存储数据, 存在静态空间管理的弊端. 我们可以使用List来代替Vector, 使用动态的空间管理措施. 

列表的数等于顶点总数n, 每条边只存放一次(有向图), 两次(无向图), 空间总量为O(n+e).

需要某些方面的时间代价作为补偿: 判断顶点u和v的联边是否存在, exists函数需要对边进行遍历, 需要O(n)时间

但与顶点相关的接口, 时间性能依旧甚至有所提升, **节点插入可以在O(1)时间内完成, 删除仍需要遍历所有临接表, 需要O(e)时间**

尽管临接表访问单条边的效率不高, 但很擅长**批量访问**, 处理同一节点的所有相连边. 只需要O(1+outDgree(v))而非O(n)时间. 

总体而言, 临接表的效率更高.

## Graph traverse

图的遍历需要访问所有的节点一次且仅一次; 此外图遍历还需要访问所有的边一次且仅一次. 

图的遍历可以理解为: 将非线性结构转化为半线性结构. 经遍历而确定的边中, 最重要的类型为**树边**, 它们和所有的节点共同构成了一棵支撑树. 

图中顶点之间可能存在多条通路，故为避免对顶点的重复访问，在遍历的过程中，通常还要动态地设置各顶点不同的状态，并随着遍历的进程不断地转换状态，直至最后的“访问完毕”。 图的遍历更加强调对处于特定状态顶点的甄别与查找，故也称作图搜索.

深度优先, 广度优先, 最佳优先等图搜索都可以在线性时间内完成O(n+e)

**各种图搜索之间的区别:** 体现在边分类结果的不同, 以及获得遍历树(森林)的结构的差异. **决定因素在于搜索中的每一步迭代, 按何种策略来选下一接受访问的顶点.**

### BFS

策略: 越早被访问到的节点, 其邻居越优先被调用. 

> 反复从波峰集中找到最早被访问到顶点v，若其邻居均已访问到，则将其逐出波峰集;否则，随意选出一个尚未访问到的邻居，并将其加入到波峰集中.

**将BFS应用于树结构等价于层次遍历**

由于每一步迭代都有一个顶点被访问到, 最多迭代O(n)步. 因为不会遗漏每个顶点的邻居, 所以对于无向图一定可以覆盖连通分量; 有向图一定可以覆盖可达分量. 

```cpp
template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s){
    reset(); // reset all status
    int clock = 0;
    int v =s;
    if(status(v) == UNDISCOVERED) 
        BFS(v,clock);
    v++; // if node havn't been discovered, BFS it!!!
    while(s!=v){
        if(status(v) == UNDISCOVERED)  
            BFS(v,clock);
        v = (++v)%n;
    }
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int &clock)
{
    Queue<int> Q; // a queue to assit
    status(v) = DISCOVERED; 
    Q.enqueue(v);
    while(!Q.empty()){ 
        int v = Q.dequeue(); // get the head node
        dTime(v) = ++ clock;
        for(int u = firstNbr(v); -1 < u; u = nextNbr(v, u)){
            // visit its all neighbors.
            if(UNDISCOVERED == status(u)){ 
                // if the neighbor havn't been visited, enqueue.
                // this edge is an edge of the search-tree
                // in the tree, its parent is v
                status(u) = DISCOVERED;
                Q.enqueue(u);
                type(v, u)= TREE;
                parent(u) = v;
            }else{
                // else this node is useless for the search-tree.
                type(u,v) = CROSS;
            }
        }
        status(v) = VISITED;
        // when its all neighbors have been discovered, this node's work done. 
    }
}
```

空间复杂度 = 队列 + 记录点的状态向量 + 记录边的状态向量 = O(n) + O(n) + O(e) = O(n+e)

时间复杂度: bfs= O(n); BFS=O(n+e) 每个顶点和边均只需要O(1)的时间访问

**常用于连通域分解和最短路径**

### DFS

策略: 优先选择最后一个被访问到的顶点的邻居.

顶点s为基点的DFS搜索，将首先访问顶点s;再从s所有尚未访问到的邻居中任取 其一，并以之为基点，递归地执行DFS搜索。

**故各顶点被访问到的次序，类似于树的先序遍历**:遇到一个节点就访问 

**而各顶点被访问完毕的次序，则类似于树的后序遍历**:等该节点的子节点访问完毕后, 该节点再访问完毕.

```cpp
template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s)
{   
    // like dfs, just traverse all the nodes, and call DFS()
    reset();
    int clock = 0;
    int v =s;
    if(status(v++) == DISCOVERED)
        DFS(v, clock);
    while(s!= v){
        if(status(v) == DISCOVERED)
            DFS(v, clock);
        v = (++v)%n;
    }
}

template<typename Tv, typename Te>
void Graph<Tv, Te>:: DFS(int v, int & clock)
{
    dTime(v) = ++clock; status(v) = DISCOVERED;
    for(int u = firstNbr(v); -1< u; u = nextNbr(v, u)){
        // travese all the neighbors
        switch(status(u)){
            case UNDISCOVERED: // not discovered, deep in!
                type(u,v) = TREE; parent(u)=v; DFS(u, clock); break;
                // and this edge will be a edge of the dfs-tree
            case DISCOVERED:   // discovered, 
                type(u,v) = BACKWARD; break;
                // it means find a loop, u is v's ancestor.
                // explanation: already find u, and v find u later. 
                // so u is dicovered precede v.
                // so u is ancestor of v.
                // who is been pointed is the elder one.
            default: 
                type(u,v) = (dTime(v) < dTime(u)) ? FORWARD : CROSS; break;
                // if node is visted, v precede u, (u,v)is forward edge
                // else they come from two different branch. 
                // the edge is cross edge.
        }
    }
    status(v) = VISITED;
    fTime(v) = ++clock;
    // this node's visited time is over
}
```

事实上, 我们通过前面对DFS的遍历状态的定义:`访问类似于先序遍历, 结束类似于后序遍历`, 可以得知: 只要两个节点的活跃时间有重合, 那么它们一定是祖先-后代关系.

空间复杂度: (节点时间标签 + 节点状态标签) + 边分类标签 = O(n) + O(e) = O(n+e)

时间复杂度: dfs = O(n); DFS()=O(n+e) (对每条边和节点的耗时均为O(1))

**常用于可达性判断, 连通域分解, DAG图判断, 拓扑排序**

## Topological Sorting

给定描述某一实际应用的有向图, 如何在与该图“相容”的前提下, 将所有点排成一个线性序列.  相容: 每一顶点都不会通过边指向其在此序列中的前驱顶点. —— 这样的线性序列称为原有向图的一个拓扑排序.

**不含环的有向图——有向无环图, 一定存在拓扑排序. 存在拓扑排序的图一定是有向无环图.**

这是因为有向无环图对应**偏序关系**, 而拓扑排序对应**全序关系**, 顶点数目有限时, 与任一偏序相容的全序必然存在. 

算法1:

任一有限偏序集中, 必有极值元素; 任一有向无环图也必然包括入度为0的节点. **只要将入度为0的顶点m(及其边)从图G中取出, 剩余的G' 依然是有向无环图, 其拓扑排序依然存在.**

**因此, 只要得到G'的拓扑排序, 只需要将m作为最大顶点插入, 即可得到G的拓扑排序.**

算法2:

有限偏序集中也存在极小元素, 以该元素为顶点, 出度为0. (DFS中转换至VISITED状态的顶点也有此性质), 且DFS中被标记为VISITED的顶点及关联边对后续的搜索过程将不起任何作用. 因此转换为VISITED状态等价于: 从图中剔除了m(及其关联边)之后的出度为0——在拓扑排序中，该顶点应为顶点m的前驱. 

因此VISITED次序正好是**拓扑排序的逆序**. 且DFS一旦发现后向边(环)即可终止算法.

```cpp
template <typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s){
    reset();
    int clock =0; int v =s;
    Stack<Tv>* S = new Stack<Tv>;
    do{
        if(status(v) == UNDISCOVERED){
            if(!Tsort(v, clock, S)){
                // if find loop, empty the stack.
                while(!S->empty())
                    S->pop(); break;
            }
        }
    }while(s!=(v= (++v%n)));
    return S;
}

template<typename Tv, typename Te>
bool Graph<Tv, Te>::Tsort(int v, int& clock, Stack<Tv>* S){
    dTime(v) = ++clock; status(v) = DISCOVERED;
    for(int u = firstNbr(v); -1<u; u = nextNbr(v,u)){
        // get all neighbors
        switch(status(u)){
            case UNDISCOVERED:
                parent(u) = v; type(u,v)=TREE;
                if(!(Tsort(u,clock, S)))
                    return false;
                // if not discovered, deep in it.
                break;
            case DISCOVERED:
                type(u,v) = BACKWARD;
                return false;
                // if find loop, return false, there is no dag
            default: type(u,v) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
            // else identify the forward and cross edge.
            break;
        }
    }
    status(v) = VISITED;
    S->push(vertex(v));
    // after tag it as visited, push it to stack.
    return true;
}
```

**相比DFS算法, 引入一个存放VISITED顺序的栈**, 空间小于O(n).

因此空间复杂度仍为 O(n+e), 时间复杂度仍为O(n+e)

## 双连通域分解

对于无向图G, 若删除顶点v后G包含的连通域增多, 则称v为切割节点(关节点). 

不含任何关节点的图称作**双连通图**, 任一无向图都可视作若干个极大的双连通子图组合而成, 每一个子图都是原图的一个双连通域. 

**蛮力算法**

首先: 通过BFS/DFS统计出图G所含连通域数目, 然后逐一枚举每个顶点v, 暂时将其从图中删去. 再次统计连通域数目, 若有增加, 则为关节点. 

时间复杂度: O(n(n+e))

****

**可行算法**

尽管搜索树丢失了很多信息, 但也有能被利用的:

1. DFS树的叶节点绝不可能是关节点. 

2. DFS树的根节点若至少有两个分支, 则必然是一个关节点.

3. 内部节点, 若c的移除导致其一棵子树与其祖先无法连通, 则c必为关节点. 若c的所有真子树都能与c的某一祖先连通, 则c不可能是关节点. 

在无向图的DFS树中, C的真子树只可能通过后向边和C的真祖先连通, 因此只要在DFS搜索过程中记录更新各点的能连通的最高祖先(highest connected ancestor), 即可及时认定关节点. 

```cpp
template<typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int s){
    reset(); int clock =0; int v =s; Stack<int> S; 
    //stack to record articulation points
    do{
        if(status(v)==UNDISCOVERED){
            BCC(v, clock, S);
            S.pop(); // pop the connect component's start
        }
    }while(s!=(v=(++v)%n));
}

#define hca(x) (fTime(x)) //闲置的ftime当hca
template <typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int v, int& clock, Stack<int>& S)
{
    hca(v)=dTime(v)=++clock;
    status(v) = DISCOVERED; S.push(v);
    for(int u = firstNbr(v); -1<u; u=nextNbr(v,u)){
        switch(status(u)){
            case UNDISCOVERED:
                parent(u)=v; type(v,u)= TREE; BCC(u,clock,S);
                if(hca(u)<dTime(v)) //u可指向v的真祖先
                    hca(v) = std::min(hca(v),hca(u)); //那么v也如此
                else{ // 否则以v为关节点(u以下即是一个BCC，且其中顶点此时正集中栈S的顶部)
                    while(v!=S.pop());
                    //依次弹出当前BCC中的节点，亦可根据实际需求转存至其它结构
                    S.push(v);//最后一个节点重新入栈, 总计至多两次.
                }
                break;
            case DISCOVERED:
                type(v,u) = BACKWARD;
                if(u!=parent(v)) hca(v) = std::min(hca(v), dTime(u));
                // 更新hca(v)
                break;
            default:
                type(v,u) = (dTime(v)<dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) =VISITED;
}
#undef hca
```
故若hca[ u ] > dTime[ v ]，则说明u及其后代无法通过后向边与v的真祖先连通，故v为关节点。既然栈S存有搜索过的顶点，与该关节点相对应的双连 通域内的顶点，此时都应集中存放于S顶部，故可依次弹出这些顶点。v本身必然最后弹出，作为 多个连通域的联接枢纽，它应重新进栈。

反之若hca[ u ] < dTime[ v ]，则意味着u可经由后向边连通至v的真祖先。果真如此，则这一性质对v同样适用，故有必要将hca[ v ]，更新为hca[ v ]与hca[ u ]之间的更小者。

当然，每遇到一条后向边(v, u)，也需要及时地将hca[ v ]，更新为hca[ v ]与dTime[ u ]之间的更小者，以保证hca[ v ]能够始终记录顶点v可经由后向边向上连通的最高祖先。

只增加了一个规模为O(n)的辅助栈, 空间复杂度O(n+e), 时间复杂度O(n+e)

## 优先级搜索

以上的搜索算法虽然各有不同, 但基本框架都有所相似.(通过迭代逐一发现各节点, 纳入遍历树并进行处理), 之间的差异主要体现在每一步迭代中对新顶点的选取策略不同(BFS选更早发现的节点, DFS选最后发现的节点).

即给顶点赋予的优先级不同, 但都是选择优先级最高的节点. 故这里不妨约定优先级数越大(小)顶点的优先级越低(高)。相应地，在算法的初始化阶段(如代码6.1中的reset())， 通常都将顶点的优先级数统一置为最大(比如对于int类型，可采用INT_MAX) 即优先级最低。

```cpp
template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater){
    reset();
    int v =s;
    do {
        if(status(v)== UNDISCOVERED)
            PFS(v, prioUpdater);
    }while(s!=(v=(++v%n)));
}

template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::PFS(int s, PU prioUpdater){
    priority(s) =0; status(s) = VISITED; // point add into PFS-tree
    parent(s) = -1;
    while(1){
        for(int w= firstNbr(s); -1<w; w= nextNbr(s,w))
            prioUpdater(this, s, w); // update w's priority and its parent
        for(int shortest= INT_MIN, w =0; w<n; ++w){
            if(UNDISCOVERED == status(w)){
                if(shortest > priority(w)){
                    shortest = priority(w);
                    s = w; // get the biggest priority point
                }
            }
        }
        if(status(s) == VISITED) break; 
        // if the best points are all added, end.
        status(s) = VISITED; type(parent(s), s)= TREE;
        // else turn it into visited, add to the tree.
    }
}
```

时间复杂度 O(n^2)

## 最小支撑树

连通图G的某一无环连通子图T覆盖G中的所有节点, 则称为G的一棵支撑树/生成树

**支撑树既是"禁止环路"前提下的极大子图, 也是"保持连通"前提下的最小子图**. 尽管一幅图可能有多棵支撑树, 但都是由n个节点, n-1条边构成的.

**蛮力算法: 逐一考察图的所有支撑树, 得到最低值.** 根据`cayley`公式可知由n个互异点组成的完全图共有n^(n-2)棵支撑树.代价无法接受

****

**Prime 算法**

思路: 最小支撑树总是会采用联接每一割的最短跨越边. 使用**贪心策略**,每一步迭代之前，假设已经得到最小支 撑树T的一棵子树Tk = (Vk; Ek)，其中Vk包含k个顶点，Ek包含k - 1条边。于是，若将Vk及其补 集视作原图的一个割，则在找到该割的最短跨越边ek = (vk, uk)( $v_k \in V_k$ 且 $ u_k \not \in V_k$)之后，即可 将Tk扩展为一棵更大的子树 $ Tk+1 = (V_{k+1}; E_{k+1})$ ，其中$V_{k+1} = V_k \cup {u_k}，E_{k+1} = E_k \cup {e_k}$。 最初的T1不含边而仅含单个顶点，故可从原图的顶点中任意选取.

可借助优先级搜索的算法实现, 每次由$T_k$扩充到$T_{k+1}$时, 可将$V_k$外的每个顶点u到$V_k$的距离视作u的优先级. 如此, 拥有最短跨越边的$u_k$就会被选中.

```cpp
template <typename Tv, typename Te> struct PrimePU
{
    virtual void operator() (Graph<Tv, Te>* g, int v, int uk){
        if(UNDISCOVERED == g->status(uk)){
            if(g->priority(uk) > g->weight(v, uk)){
                g->priority(uk) = g->weight(v, uk);
                g->parent(uk) = v;
            }
        }
    }
};
```

上述的更新器只需要O(1)时间, 所以prime算法的时间复杂度为O(n+e)

## 最短路径

给定带权网络G =(V,E), 以及源点 $s \in V$, 对于其他节点v, s到v的最短通路有多长, 由哪些边构成?

策略: 若顶点s到v的最短路径为p, 于是对于该路径上的任一顶点u, 若其在p上对应的前缀为o, 则o也是从s到u的最短路径(之一)

因为路径肯定无环, 所以最短路径应该是一棵**最短路径树**.

**Dijkstra算法**

将顶点$u_i$到起点s的距离记作: $d_i = dist(s, u_i), 1 \leq i \leq n$. 不妨设$d_i$按非降序排列. 即$di \leq dj$当且仅当$i \leq j$。于是与s自身相对应地必有:u1 = s。

最短路径树$T_1$仅含单个节点s, $T_n=T$. 实际上 $T_k$一定是一棵树, 为验证这一点，只需归纳证明 Tk是连通的。为从Tk+1转到Tk而删除的顶点uk+1，在Tk+1中必是叶节点。而根据最短路径的单调性， 作为Tk+1中距离最远的顶点，uk+1不可能拥有后代。

因此算法的**贪心策略为**:只要能找到$u_{k+1}$, 即可对当前最短路径树进行扩充. 每一个顶点uk+1都是在Tk之外，距离s最近者将此距离作为各顶点的优先级数，则与最小支撑树的Prim算法类似，每次将uk+1加入Tk并将其 拓展至Tk+1后，需要且只需要更新那些仍在Tk+1之外，且与Tk+1关联的顶点的优先级数。

可见，该算法与Prim算法仅有一处差异:考虑的是uk+1到s的距离，而不再是其到Tk的距离.

```cpp
template <typename Tv, typename Te>
struct DijkstraPU{
    virtual void operator() (Graph<Tv, Te>* g, int uk, int v){
        if(g->status(uk) == UNDISCOVERED){
            if(g->priority(uk) > g->priority(v)+g->weight(v, uk)){
                g->priority(uk) = g->priority(v)+g->weight(v, uk);
                g->parent(uk) = v;
            }
        }
    }
};
```
同样, 迭代器只需要常数时间, 因此Dijkstra算法的时间复杂度为O(n^2).

