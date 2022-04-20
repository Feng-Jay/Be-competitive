#ifndef _GRAPH_MARTIX_H_
#define _GRAPH_MARTIX_H_
#include "../Chapter2_Vector/vector.h"
#include "graph.h"

template <typename Tv>
struct Vertex{ // 顶点对象
    Tv data; int inDegree; int outDegree;
    VStatus status;
    int dTime, fTime;
    int parent; int priority;
    Vertex(Tv const& d = (Tv) 0):
        data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
        dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){}
};

template <typename Te>
struct Edge
{
    Te data;
    int weight; 
    EType type;
    Edge(Te const& d, int w):data(d), weight(w), type(UNDETERMINED){}
};


template <typename Tv, typename Te>
class GraphMartix: public Graph<Tv, Te>{
private:
    Vector< Vertex<Tv> > V; // nodes set
    Vector< Vector<Edge<Te>*> > E; // edge set, the martix
public:
    GraphMartix(){this->n=this->e=0;}
    ~GraphMartix(){
        for(int j =0; j<this->n; ++j){
            for(int k =0; k<this->n; ++k){
                delete E[j][k];
            }
        }
    }
    // static op
    virtual Tv& vertex(int i){return V[i].data;}
    virtual int inDegree(int i){return V[i].inDegree;}
    virtual int outDegree(int i){return V[i].outDegree;}
    virtual int firstNbr(int i){return nextNbr(i,this->n);}
    virtual int nextNbr(int i, int j){
        j--;
        while((-1<j)&&(!this->exists(i, j)))
            j--; 
        return j;
    }
    virtual VStatus& status(int i){return V[i].status;}
    virtual int& dTime(int i){return V[i].dTime;}
    virtual int& fTime(int i){return V[i].fTime;}
    virtual int& parent(int i){return V[i].parent;}
    virtual int& priority(int i){return V[i].priority;}
    // dynamic op
    virtual int insert(Tv const& vertex){
        // isert a column of the martix
        for(int j=0; j<this->n; ++j){
            E[j].insert(NULL);
        }
        this->n++;
        // insert a row of the martixss
        E.insert(Vector< Edge<Te>* >(this->n, this->n, (Edge<Te>*)NULL));
        return V.insert(Vertex<Tv>(vertex));
    }
    virtual Tv remove(int i){
        for(int j=0; j<this->n; ++j){
            if(this->exists(i,j)){
                delete E[i][j]; V[j].inDegree--;
            }
        }
        E.remove(i); this->n--;
        Tv vBAK =vertex(i); V.remove(i);
        for(int j=0; j<this->n; ++j){
            if(Edge<Te>*e = E[j].remove(i)){
                delete e;
                V[j].outDegree--;
            }
        }
        return vBAK;
    }
    virtual bool exists(int i, int j){
        return (0<=i)&&(i<=this->n)&&(0<=j)&&(j<this->n)&&E[i][j]!=NULL;
    }
    virtual EType& type(int i, int j){
        return E[i][j]->type;
    }
    virtual Te& edge(int i, int j){
        return E[i][j]->data;
    }
    virtual int& weight(int i, int j){
        return E[i][j]->weight;
    }
    virtual void insert(Te const& edge, int w, int i, int j){
        if(exists(i,j)) return;
        E[i][j] = new Edge<Te> (edge, w);
        this->e++;
        V[i].outDegree++;
        V[j].inDegree++;
    }
    virtual Te remove(int i, int j){
        Te eBak=edge(i,j);
        delete E[i][j];
        E[i][j] = NULL;
        this->e--;
        V[i].outDegree--;
        V[j].inDegree++;
        return eBak;
    }

};

// #include "graph_martix.cpp"s

#endif