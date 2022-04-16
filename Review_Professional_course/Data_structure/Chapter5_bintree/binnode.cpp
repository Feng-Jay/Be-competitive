#include "binnode.h"
template <typename T>
inline int stature(BinNodePosi(T) p){return (p)? (p)->height : -1;}


// quick ways
template <typename T>
inline bool Isroot(BinNode<T> const& x){return !((x).parent);}

template <typename T>
inline bool IsLChild(BinNode<T> const& x){return !Isroot(x) && (&(x) == (x).parent->lc);}

template <typename T>
inline bool IsRChild(BinNode<T> const& x){return !Isroot(x) && (&(x) == (x).parent->rc);}

template <typename T>
inline bool HasParent(BinNode<T> const& x) { return !Isroot(x);}

template <typename T>
inline bool HasLChild(BinNode<T> const& x) { return x.lc; }

template <typename T>
inline bool HasRChild(BinNode<T> const& x) { return x.rc; }

template <typename T>
inline bool HasChild(BinNode<T> const& x){ return HasLChild(x)||HasRChild(x);}

template <typename T>
inline bool HasBothChild(BinNode<T> const& x){return HasLChild(x)&&HasRChild(x);}

template <typename T>
inline bool IsLeaf(BinNode<T> const& x) {return !HasChild(x);}

template <typename T>
inline BinNodePosi(T) sibling(BinNode<T> const& x) {return IsLChild(x) ? x.parent->rc : x.parent->lc; }

template <typename T>
inline BinNodePosi(T) uncle(BinNode<T> const& x){ return IsLChild(*(x.parent)) ? x.parent->parent->rc : x.parent->parent->lc; }

template <typename T>
inline BinNodePosi(T) FromParentTo(BinNode<T> const & x){
    // if is root, return NULL
    // else return the pointer
    return Isroot(x) ? NULL : (IsLChild(x)? x.parent->lc : x.parent->rc);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e){
    return lc = new BinNode(e, this);
}
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e){
    return rc = new BinNode(e, this);
}

// recursive traverse. 
template <typename T, typename VST>
void travpre_R(BinNodePosi(T)x, VST& visit)
{
    if(!x) return;
    visit(x);
    travpre_R(x->lc, visit);
    travpre_R(x->rc, visit);
}

template <typename T, typename VST>
void travpost_R(BinNodePosi(T)x, VST& visit)
{
    if(!x) return;
    travpost_R(x->lc,visit);
    travpost_R(x->rc, visit);
    visit(x);
}

template <typename T, typename VST>
void travin_R(BinNodePosi(T) x, VST& visit)
{
    if(!x) return ;
    travin_R(x->lc, visit);
    visit(x);
    travin_R(x->rc, visit);
}

template <typename T>
template <typename VST>
void BinNode<T>::travIn(VST& visit)
{
    switch (std::rand()%5)
    {
    case 1: travIn_v1(this, visit); break;
    case 2: travIn_v2(this, visit); break;
    case 3: travIn_v3(this, visit); break;
    case 4: travIn_v4(this, visit); break;
    default: travIn_R(this, visit); break;
    }
}