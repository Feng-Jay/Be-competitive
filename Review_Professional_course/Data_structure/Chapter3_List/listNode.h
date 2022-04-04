#include <iostream>

typedef int Rank;

#define ListNodePosi(T) ListNode<T>*

template <typename T> struct ListNode{
    // member variables
    T data;
    ListNodePosi(T) pred;// pre
    ListNodePosi(T) succ;// successive

    // constructor
    ListNode(){}
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL):
        data(e), pred(p), succ(s){}
    
    // op
    ListNodePosi(T) insertAsPred(T const& e);// insert before this node
    ListNodePosi(T) insertAsSucc(T const& e);// insert after this node
};