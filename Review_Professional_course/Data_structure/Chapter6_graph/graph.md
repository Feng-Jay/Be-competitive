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