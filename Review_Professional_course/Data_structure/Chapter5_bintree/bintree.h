#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_
#include "binnode.h"
template <typename T> 
class Bintree{

protected:
    int _size; BinNodePosi(T) _root;
    virtual int updateHeight(BinNodePosi(T) x); // update nodex's height
    void updateHeightAbove(BinNodePosi(T)x); // update x and its ancestors' height
public: 
    Bintree(): _size(0), _root(NULL){}
    ~Bintree(){if(0 < _size) remove(_root);}
    // inline func
    int size() const{ return _size;}
    bool empty() const{ return !_size;}
    BinNodePosi(T) root() const{ return _root;}
    // writable func
    BinNodePosi(T) insertAsRoot(T const& e);
    BinNodePosi(T) insertAsLC(BinNodePosi(T)x, T const& e); // insert as left child
    BinNodePosi(T) insertAsRC(BinNodePosi(T)x, T const& e); // insert as right child
    BinNodePosi(T) attachAsLC(BinNodePosi(T)x, Bintree<T>* &t); // attach as left-subtree
    BinNodePosi(T) attachAsRC(BinNodePosi(T)x, Bintree<T>* &t); // attach as right-subtree
    int remove(BinNodePosi(T) x); // delete root x's subtree, return original scale.
    Bintree<T>* secede(BinNodePosi(T) x); // delete root x's subtree, and become a new tree
    // traverse func
    template<typename VST>
    void travLevel(VST& visit){if(_root) _root->travLevel(visit);}
    template<typename VST>
    void travPre(VST& visit){if(_root) _root->travPre(visit);}
    template<typename VST>
    void travIn(VST& visit){if(_root) _root->travIn(visit);}
    template<typename VST>
    void travPost(VST& visit){if(_root) _root->travPost(visit);}

    // reload operator
    bool operator< (Bintree<T> const& t){
        return _root && t._root && ((_root->data) < (t._root->data));
    }

    bool operator==(Bintree<T> const& t){
        return _root && t._root && (_root == t._root);
    }
};
#include "bintree.cpp"

#endif 