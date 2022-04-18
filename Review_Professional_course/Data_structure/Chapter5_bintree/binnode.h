#ifndef _BIN_NODE_
#define _BIN_NODE_
#define BinNodePosi(T) BinNode<T>*
#include <iostream>
#include "../Chapter4_stack&queue/stack.h"
#include "../Chapter4_stack&queue/queue.h"

// #define stature(p) ((p) ? (p)->height : -1)
typedef enum{RB_RED, RB_BLACK} RBColor;

template<typename T> 
struct BinNode{
    T data; 
    BinNodePosi(T) parent; 
    BinNodePosi(T) lc;
    BinNodePosi(T) rc;
    int height; 
    int npl; // null path length(左式堆)
    RBColor color; // color red-black tree
    // contructor
    BinNode(): parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED){}
    BinNode(T e, BinNodePosi(T) p=NULL, BinNodePosi(T) lc=NULL, BinNodePosi(T) rc =NULL, int h=0, int l =1, RBColor c =RB_RED):
    data(e), parent(p), lc(lc),rc(rc), height(h), npl(l), color(c){}

    // api
    int size(); // get the number of its decendant
    BinNodePosi(T) insertAsLC(T const&); 
    BinNodePosi(T) insertAsRC(T const&);
    BinNodePosi(T) succ(); 

    template <typename VST> void travLevel(VST&); //traverse subtree by level
    template <typename VST> void travPre(VST&);   //traverse subtree by pre-order
    template <typename VST> void travIn(VST&);    //traverse subtree by in-order
    template <typename VST> void travPost(VST&);  //traverse subtree by post-order

    // operator
    bool operator< (BinNode const& bn){return data< bn.data;}
    bool operator== (BinNode const& bn){return data == bn.data;}
};

#include "binnode.cpp"
#endif
