#include "graph.h"

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s){
    reset();
    int clock = 0;
    int v =s;
    if(status(v) == UNDISCOVERED) 
        BFS(v,clock);
    v++;
    while(s!=v){
        if(status(v) == UNDISCOVERED)  
            BFS(v,clock);
        v = (++v)%n;
    }
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int &clock)
{
    Queue<int> Q;
    status(v) = DISCOVERED;
    Q.enqueue(v);
    while(!Q.empty()){
        int v = Q.dequeue();
        dTime(v) = ++ clock;
        for(int u = firstNbr(v); -1 < u; u = nextNbr(v, u)){
            if(UNDISCOVERED == status(u)){
                status(u) = DISCOVERED;
                Q.enqueue(u);
                type(v, u)= TREE;
                parent(u) = v;
            }else{
                type(u,v) = CROSS;
            }
        }
        status(v) = VISITED;
    }
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s)
{
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
        switch(status(u)){
            case UNDISCOVERED:
                type(u,v) = TREE; parent(u)=v; DFS(u, clock); break;
            case DISCOVERED:
                type(u,v) = BACKWARD; break;
            default: 
                type(u,v) = (dTime(v) < dTime(u)) ? FORWARD : CROSS; break;
        }
    }
    status(v) = VISITED;
    fTime(v) = ++clock;
}

template <typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s){
    reset();
    int clock =0; int v =s;
    Stack<Tv>* S = new Stack<Tv>;
    do{
        if(status(v) == UNDISCOVERED){
            if(!Tsort(v, clock, S)){
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
        switch(status(u)){
            case UNDISCOVERED:
                parent(u) = v; type(u,v)=TREE;
                if(!(Tsort(u,clock, S)))
                    return false;
                break;
            case DISCOVERED:
                type(u,v) = BACKWARD;
                return false;
            default: type(u,v) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
            break;
        }
    }
    status(v) = VISITED;
    S->push(vertex(v));
    return true;
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int s){
    reset(); int clock =0; int v =s; Stack<int> S; //stack to record visited nodes
    do{
        if(status(v)==UNDISCOVERED){
            BCC(v, clock, S);
            S.pop(); // pop the connect component's start
        }
    }while(s!=(v=(++v)%n));
}

#define hca(x) (fTime(x))
template <typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int v, int& clock, Stack<int>& S)
{
    hca(v)=dTime(v)=++clock;
    status(v) = DISCOVERED; S.push(v);
    for(int u = firstNbr(v); -1<u; u=nextNbr(v,u)){
        switch(status(u)){
            case UNDISCOVERED:
                parent(u)=v; type(v,u)= TREE; BCC(u,clock,S);
                if(hca(u)<dTime(v)) //u指向v的真祖先
                    hca(v) = std::min(hca(v),hca(u)); //那么v也如此
                else{ // 否则以v为关节点
                    while(v!=S.pop());
                    S.push(v);
                }
                break;
            case DISCOVERED:
                type(v,u) = BACKWARD;
                if(u!=parent(v)) hca(v) = std::min(hca(v), dTime(u));
                break;
            default:
                type(v,u) = (dTime(v)<dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) =VISITED;
}
#undef hca

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
    priority(s) =0; status(s) = VISITED;
    parent(s) = -1;
    while(1){
        for(int w= firstNbr(s); -1<w; w= nextNbr(s,w))
            prioUpdater(this, s, w);
        for(int shortest= INT_MIN, w =0; w<n; ++w){
            if(UNDISCOVERED == status(w)){
                if(shortest > priority(w)){
                    shortest = priority(w);
                    s = w;
                }
            }
        }
        if(status(s) == VISITED) break;
        status(s) = VISITED; type(parent(s), s)= TREE;
    }
}

template <typename Tv, typename Te> struct PrimePU
{
    virtual void operator() (Graph<Tv, Te>* g, int uk, int v){
        if(UNDISCOVERED == g->status(v)){
            if(g->priority(v) > g->weight(uk, v)){
                g->priority(v) = g->weight(uk, v);
                g->parent(v) = uk;
            }
        }
    }
};

template <typename Tv, typename Te>
struct DijkstraPU{
    virtual void operator() (Graph<Tv, Te>* g, int uk, int v){
        if(g->status(v) == UNDISCOVERED){
            if(g->priority(v) > g->priority(uk)+g->weight(uk, v)){
                g->priority(v) = g->priority(uk)+g->weight(uk,v);
                g->parent(v) = uk;
            }
        }
    }
};
