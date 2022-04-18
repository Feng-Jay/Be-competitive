#include "bintree.h"

// a node's height == the max height of its children. 
// when insert or delete nodes, height may change.
// so when these things happened, update nodes' height.
template<typename T>
int Bintree<T>::updateHeight(BinNodePosi(T) x)
{
    return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
}
template <typename T>
void Bintree<T>::updateHeightAbove(BinNodePosi(T) x)
{
    while(x){
        Bintree<T>::updateHeight(x);
        x= x->parent;
    }
}

template <typename T>
BinNodePosi(T) Bintree<T>::insertAsRoot(T const& e)
{
    _size = 1;
    return _root = new BinNode<T>(e);
}
template <typename T>
BinNodePosi(T) Bintree<T>::insertAsLC(BinNodePosi(T) x ,T const& e)
{
   _size++;
   x->insertAsLC(e);
   updateHeightAbove(x);
   return x->lc; 
}
template <typename T>
BinNodePosi(T) Bintree<T>::insertAsRC(BinNodePosi(T) x, T const& e )
{
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}
template <typename T>
BinNodePosi(T) Bintree<T>::attachAsLC(BinNodePosi(T) x, Bintree<T>* &s )
{
    x->lc = s->_root;
    x->lc->parent=x;
    _size+= s->_size; 
    updateHeightAbove(x);
    s->_root =NULL; s->_size = 0;
    // delete s; 
    s=NULL;
    return x;
}
template <typename T>
BinNodePosi(T) Bintree<T>::attachAsRC(BinNodePosi(T)x, Bintree<T>* & s)
{
    x->rc=s->_root;
    x->rc->parent = x;
    _size+= s->_size;
    updateHeightAbove(x);
    s->_root = NULL; s->_size = 0;
    // delete s; 
    // s指向了一棵树, 树内有很多指针和数据
    // 现在s已经不再需要了, 我们会删除s内分配在heap上的数据
    s= NULL;
    return x;
}
template <typename T>
static int  removeAt(BinNodePosi(T) x)
{
    if(!x) return 0;
    int n = 1+ removeAt(x->lc) + removeAt(x->rc);
    // delete x->data;
    x->data = 0;
    delete x; 
    return n;
}

template <typename T>
int Bintree<T>::remove(BinNodePosi(T) x)
{
    if(!x) return 0; // empty tree
    // BinNodePosi(T) temp = FromParentTo(*x);
    if (IsLChild(*x)) x->parent->lc = NULL;
    else if(IsRChild(*x)) x->parent->rc = NULL;
    // temp = NULL;
    updateHeightAbove(x);
    int n = removeAt(x); _size -=n; return n;
}

template <typename T>
Bintree<T>* Bintree<T>::secede(BinNodePosi(T) x)
{
    if (IsLChild(*x)) x->parent->lc = NULL;
    else x->parent->rc = NULL;
    // std::cout<<FromParentTo(*x)<<std::endl;
    updateHeightAbove(x);
    Bintree<T>* s = new Bintree<T>;
    s->_root = x;
    s->_root->parent = NULL;
    // x->parent = NULL;
    s->_size = x->size();
    _size -= s->_size;
    return s;
}
