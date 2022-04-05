#include "list.h"

template <typename T> 
void List<T>:: init(){
    header = new ListNode<T>;
    tailer = new ListNode<T>;
    header->succ= tailer; header->pred=NULL;
    tailer->succ= NULL; tailer->pred= header;
    _size= 0;
}

template <typename T>
T& List<T>:: operator[] (Rank r) const{
    ListNodePosi(T) p =first();
    while(0< r--){
        p = p->succ;
    }
    return p->data;
}

template <typename T>
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const{
    while(0<n--){
        p = p->pred;
        if(e == p->data) return p;
    }
    return NULL;
}

template <typename T>
ListNodePosi(T) List<T>:: insertAsFirst(T const& e){
    _size++;
    return header->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>:: insertAsLast(T const& e){
    _size++;
    return tailer->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>:: insertA(ListNodePosi(T) p, T const& e){
    _size++;
    p->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>:: insertB(ListNodePosi(T) p, T const& e){
    _size++;
    p->insertAsPred(e);
}

template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n){
    init();
    while(n--){
        insertAsLast(p->data);
        p=p->succ;
    }
}

template <typename T>
List<T>::List(ListNodePosi(T) p, int n){
    copyNodes(p, n);
}

template <typename T>
List<T>:: List(List<T> const& L){
    copyNodes(L.first(), L._size);
}

template <typename T>
List<T>:: List(List<T> const& L, Rank r, int n){
    copyNodes(L[r], n);
}

template <typename T>
T List<T>:: remove(ListNodePosi(T) p){
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}
template <typename T>
List<T>:: ~List(){
    clear();
    delete header;
    delete tailer;
}

template <typename T>
int List<T>::clear(){
    int oldsize = _size;
    while(0< _size) remove(header->succ);
    return oldsize;
}

template <typename T>
int List<T>::deduplicate(){
    if(_size < 2) return 0;
    int oldsize = _size;
    ListNodePosi(T) p = header;
    Rank r =0;
    while(tailer != p->succ){
        ListNodePosi(T) q = find(p->data, r, p);//在p的r个前驱中, 查找雷同者.
        q ? remove(q) : r++;
    }
    return oldsize - _size;
}
template <typename T>
void List<T>:: traverse(void (*visit)(T&)){
    for (ListNodePosi(T) p = header->succ; p!=tailer; p=p->succ){
        visit(p->data);
    }
}

// sorted list
// double pointer
template <typename T>
int List<T>:: uniquify(){
    if(_size<2) return;
    int oldsize = _size;
    ListNodePosi(T) p =first();
    ListNodePosi(T) q = p->succ;
    while(tailer!=q){
        // 若相等删除
        if(p->data == q->data) {
            remove(q);
            // null ptr, need to point to another place.
        }
        // 否则p和q都后移.
        else{
            p = q;
        }
        q = p->succ;
    }
    return oldsize - _size;
}

template <typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const{
    // p = p->pred;
    // search in p's n pre positions.
    while(0< n--){
        // if data equal and position is valid, return;
        p = p->pred;
        if (!valid(p)) break;
        if(p->data <= e) return p; // equal or value cannot equal
    }
    // not found or not valid pointer, return header.
    return header;
}

// sort
template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n){
    switch(std::rand()%3){
        case 1: insertionsort(p, n); break;
        case 2: selectionsort(p, n); break;
        default: mergesort(p,n); break;
    }
}
template <typename T>
void List<T>:: insertionsort(ListNodePosi(T) p, int n){
    // sort the n elems start from p
    for(int i =0; i< n; ++i){
        insertA(search(p->data,i,p),p->data);// find the first el elem, put behind it.
        p = p->succ;// after insert, this node is useless, delete it.
        remove(p->pred);
    }
}

template <typename T>
void List<T>::selectionsort(ListNodePosi(T) p, int n){
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) tail = p->succ;
    for(int i=0; i< n; ++i) tail = tail->succ;
    // get the sort space (head, tail)
    while(1< n){
        // get the min position
        ListNodePosi(T) minp = selectmin(head->succ, n);
        // insert min after head 
        insertA(head,minp->data);
        // delete min
        remove(minp);
        // head move forward
        head = head->succ;
        // only need n-1 times, the last one must be the biggest.
        n--;
    }
}
template <typename T>
ListNodePosi(T) List<T>::selectmin(ListNodePosi(T) p, int n){
    // find the min in [p, p+n)
    ListNodePosi(T) minp = p;
    for(ListNodePosi(T) cur = p; n>1; --n){
        cur = cur->succ;
        if(cur->data < minp->data)
            minp=cur;
    }
    return minp;
}

template <typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m){
    // merge previous list's [p, p+n) elems with L's [q, q+m)
    ListNodePosi(T) pp =p->pred;
    while(0< m){ // for each q's elems
        if((0<n) && (p->data <= q->data )){
            p = p->succ;
            if(q==p) break; 
            // 如果是对一个list进行merge, 那么会出现该情况
            // 表明, 排序已经完成了,q后面的数据均比当前大, 且已经在链表后连接, 无需多余操作.
            n--;
            // 我们把最后排序的结果存放在链表p中
        }
        else{
            // p越界 or p->value > q->value
            q = q->succ;
            insertB(p, L.remove(q->pred));
            m--;
        }
        p =pp->succ; // give the new start
    }
}
template <typename T>
void List<T>:: mergesort(ListNodePosi(T) &p, int n){
    if(n<2) return;
    int m = n>>1;
    ListNodePosi(T) q = p;
    for(int i=0; i< m; ++i) q = q->succ;
    mergesort(p, m); mergesort(q, n-m);
    merge(p,m,*this,q, n-m);
}