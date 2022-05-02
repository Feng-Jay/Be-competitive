#include "BST.h"

template <typename T>
static BinNodePosi(T) & searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot){
    if(!v||e==v->data) return v;
    hot = v;
    return searchIn(((e < v->data)? v->lc : v->rc), e, hot);
}

template <typename T>
BinNodePosi(T)& BST<T>::search(const T& e){
    return searchIn(_root, e, _hot=NULL);
}

template <typename T>
BinNodePosi(T) BST<T>::insert(const T& e){
    BinNodePosi(T)& x = search(e);
    if(x) return x; //if exist, return. only insert the unexist elems
    x = new BinNode<T> (e, _hot); // new node, whose parent is hot
    _size++;
    updateHeightAbove(x); // update x and x's ancestor's height.
    return x;
}

template <typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot){
    BinNodePosi(T) w = x;
    BinNodePosi(T) succ = NULL;
    if(!HasLChild(*x)) succ = x = x->rc;
    else if (!HasRChild(*x)) succ = x =x->lc;
    else {
        w = w->succ();
        std::swap(x->data, w->data);
        BinNodePosi(T) u = w->parent; // get w's parent
        // w do not have left child so... 
        // if u==x, the succ is from right child
        // if u!=x, the succ is from left child
        ((u == x)? u->rc : u->lc) = succ = w->rc;
    }
    hot = w->parent; // hot is delete-node's parent
    if(succ) succ->parent = hot; //succ's parent's parent is hot
    // release(w->data); release(w);
    delete w; w = NULL;
    return succ;
}

template <typename T>
bool BST<T>::remove(const T& e){
    BinNodePosi(T)& x = search(e);
    if(!x) return false;
    removeAt(x, _hot);
    updateHeightAbove(_hot);
    return true;
}