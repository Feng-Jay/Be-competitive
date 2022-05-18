#include "./BST.h"

template<typename T> 
class AVL: public BST<T>{
public:
    BinNodePosi(T) insert(const T&e); // re-implement
    bool remove(const T&e); // re-implement
    // BST::search()等接口可以直接沿用
}