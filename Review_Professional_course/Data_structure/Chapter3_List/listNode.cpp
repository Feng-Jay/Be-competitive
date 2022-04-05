#include "listNode.h"

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e){
    ListNodePosi(T) x = new ListNode(e, pred, this);
    // create a node, whose pred is my pred, succ is me.
    pred->succ = x;
    // my pred's succ = x
    pred = x;
    // my pred = x
    return x;
}

template <typename T>
ListNodePosi(T) ListNode<T>:: insertAsSucc(T const& e){
    ListNodePosi(T) x = new ListNode(e, this, succ);
    succ->pred =x;
    succ = x;
    return x;
}
