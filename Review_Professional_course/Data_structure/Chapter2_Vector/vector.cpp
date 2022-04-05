#include "vector.h"

template <typename T> 
Vector<T>:: Vector():
_size(0),_capacity(DEFAULT_CAPACITY)
{
    _elems = new T [_capacity];
}
// 重载的原因是:
// 由于vector 内部可能含有动态存储的空间, 简单的赋值不足以支持向量间赋值
// 因此重载 = 运算符, 支持此类情况

// 重载运算符若为类内函数, 则只需要一个参数; 否则需要两个参数
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& v){
    if(_elems) delete [] _elems; // 释放原空间
    copyFrom(v._elems, 0, v.size()); // 整体copy
    return *this; // 返回当前对象的引用, 方便链式赋值
}

template <typename T>
Vector<T>:: Vector(T const* A, Rank n){
    copyFrom(A,0,n);
}

template <typename T>
Vector<T>:: Vector(T const* A, Rank lo, Rank hi){
    copyFrom(A,lo,hi);
}

template <typename T>
Vector<T>::Vector(Vector<T> const& V){
    copyFrom(V._elems, 0, V._size);
}

template <typename T>
Vector<T>::Vector(Vector<T> const& V, Rank lo, Rank hi){
    copyFrom(V._elems,lo,hi);
}

// destructor
// problem: what if elems[i] is not a basic type?
// simplify, who alloc who realse.
template <typename T>
Vector<T>:: ~Vector(){
    delete [] this->_elems;
}

//Read-only
template <typename T>
Rank Vector<T>:: size() const{
    return this->_size;
}

template <typename T>
bool Vector<T>::empty() const{
    return !this->_size;
}

template <typename T>
Rank Vector<T>:: find(T const& e) const{
    return find(e, 0, _size);
}

template <typename T>
Rank Vector<T>:: find(T const& e, Rank lo, Rank hi) const{
    while((lo<hi--) && (_elems[hi]!=e) );
    return hi;
}

template <typename T>
int Vector<T>:: disorder() const{
    int n = 0;
    for (int i =1; i< _size; ++i){
        if(_elems[i-1] > _elems[i]) n++;
    }
    return n;
}

template <typename T>
Rank Vector<T>::search(T const& e) const{
    return (0>=_size) ? -1 :search(e, 0, _size);
}
template <typename T>
static Rank binsearch(T* A, T const& e, Rank lo, Rank hi){
    while(lo < hi){
        Rank mi = (lo+hi)>>1;
        // std::cout<<mi<<std::endl;
        (e < A[mi]) ? hi = mi : lo = mi+1;
    }
    return --lo;
}

template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const{
    return binsearch(_elems, e, lo, hi);
    // : fibsearch(_elems, e, lo, hi);
}

// template <typename T>
// static Rank binsearch(T* A, T const&e, Rank lo, Rank hi){
//     while(lo<hi){
//         Rank mi = (lo+hi)>>1;
//         if (e< A[mi]) hi =mi;
//         else if (A[mi] < e) lo = mi+1;
//         else return mi;
//     }
//     return -1;
// }

// template <typename T>
// static Rank binsearch(T* A, T const& e, Rank lo, Rank hi){
//     while(lo<hi){
//         Rank mi = (lo+hi) >>1;
//         (e < A[mi]) ? hi = mi : lo = mi;
//     }
//     return (e == A[lo]) ? lo : -1;
// }



// template <typename T>
// static Rank fibsearch(T*A, T const& e, Rank lo, Rank hi){
//     Fib fib(hi - lo); //create fib 数列
//     while(lo < hi){
//         while(hi-lo < fib.get()) fib.prev();
//         Rank mi = lo + fib.get() -1;
//         if (e<A[mi]) hi=mi;
//         else if (A[mi]<e) lo = mi+1;
//         else return mi;
//     }
//     return -1;
// }

// writeable
template <typename T>
T& Vector<T>:: operator[](Rank r) const{
    return _elems[r];
}

template <typename T>
void Vector<T>:: unsort() {
    unsort(0,_size);
}

template <typename T>
void Vector<T>:: unsort(Rank lo, Rank hi){
    T* V = _elems + lo;
    for (Rank i = hi-lo; i >0; i--){
        std::swap(V[i-1], V[rand()%i]);
    }
}

template <typename T>
Rank Vector<T>:: insert(Rank r, T const& e){
    expand(); //test it need expand or nor?
    for (int i= _size; i>r; i--) 
        _elems[i] = _elems[i-1];
    _elems[r] = e;
    _size++;
    return r;
}
template <typename T>
Rank Vector<T>:: insert(T const& e){
    return insert(_size, e);
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi){
    // delete [lo, hi)
    if(lo == hi) return 0;
    while(hi < _size) _elems[lo++] = _elems[hi++];
    _size = lo;
    shrink();
    return hi-lo;
}
template <typename T>
T Vector<T>::remove(Rank r){
    T e = _elems[r];
    remove(r,r+1);
    return e;
}

template <typename T>
int Vector<T>::deduplicate(){
    int old_size = _size;
    Rank i = 1;
    while( i < _size){
        (find(_elems[i],0,i) < 0) ? i++ : remove(i);
    }
    return old_size - _size;// return delete elem number
}

template <typename T>
int Vector<T>:: uniquify(){
    Rank i =0, j =0;
    while(++j <_size){
        if(_elems[i]!=_elems[j])
            _elems[++i] = _elems[j];
    }
    //发现不同元素时, 将其前移到前者的右边.
    _size = ++i;
    shrink();
    return j-i;
}

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi){
    switch(std::rand()%2){
        case 0: bubble_sort(lo, hi); break;
        // case 2: selectionsort(lo, hi); break;
        case 1: mergesort(lo, hi); break;
        default: std::cout<<"not implemennted"<<std::endl;
        // case 4: heapsort(lo, hi); break;
        // default: quicksort(lo, hi); break; 
    }
}

template <typename T>
void Vector<T>::sort(){
    sort(0,_size);
}

// protected 
template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi){
    this->_elems = new T [this->_capacity=2*(hi-lo)];
    _size = 0;
    while (lo < hi)
        this->_elems[_size++] = A[lo++];
    return;
}

template <typename T>
void Vector<T>:: expand(){
    if(_size < _capacity) return;
    if(_capacity< DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T* old = _elems; _elems = new T[_capacity<<=1]; //记录下旧地址, 开辟新空间
    for(int i =0; i< _size; ++i){
        _elems[i] = old[i];
    }
    delete [] old;
}

template <typename T>
void Vector<T>::shrink(){
    if(_capacity < DEFAULT_CAPACITY <<1 ) return;
    // capacity can not lower than default capacity
    if(_size<<2 > _capacity) return;
    // 25% is the limitation
    T* old = _elems;
    _elems = new T [_capacity>>=1];
    for(int i = 0; i< _size; ++i){
        _elems[i] = old[i];
    }
    delete [] old;
}

template <typename T>
void Vector<T>:: traverse(void(* visit)(T&)){
    for(int i = 0; i< _size; ++i){
        visit(_elems[i]);
    }
}

// template <typename T> 
// template<typename VST>
// void Vector<T>:: traverse(VST& visit){
//     for(int i = 0; i< _size; ++i){
//         visit(_elems[i]);
//     }
// }

template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi){
    bool sorted = true;
    while(++lo < hi){
        if(_elems[lo-1]>_elems[lo]){
            sorted = false;
            std::swap(_elems[lo-1], _elems[lo]);
        }
    }
    return sorted;
}

template <typename T>
void Vector<T>:: bubble_sort(Rank lo, Rank hi){
    while(! bubble(lo, hi--));
}
template <typename T>
void Vector<T>:: mergesort(Rank lo, Rank hi){
    if(hi - lo < 2) return ;
    int mi = (lo+hi) >>1; 
    mergesort(lo, mi);
    mergesort(mi,hi);
    merge(lo, mi, hi);
}

template <typename T>
void Vector<T>:: merge(Rank lo, Rank mi, Rank hi){
    T * A = _elems+lo;
    int lb = mi - lo;
    T * B = new T [lb];
    for(Rank i =0; i < lb; ++i){
        B[i] = A[i];
    }
    int lc = hi - mi;
    T * C =_elems+mi;
    for (Rank i=0, j=0, k=0; (i<lb)||(j<lc);){
        if((i<lb)&&(!(j<lc)||(B[i]<=C[j]))) A[k++] = B[i++];
        if((j<lc)&&(!(i<lb)||(C[j]<=B[i]))) A[k++] = C[j++];
    }
    delete [] B;
    // delete [] C;
}

template <typename T>
Rank Vector<T> :: max(Rank lo, Rank hi){
    if(!disorder()) return hi;
    Rank max1 = lo; 
    for ( Rank i = lo; i < hi; ++i){
        if(_elems[max1] < _elems[i]){
            max1 = i;
        }
    }
    return max1;
}

template <typename T> static bool lt ( T* a, T* b ) { return lt ( *a, *b ); } //less than 2 
template <typename T> static bool lt ( T& a, T& b ) { return a < b; } //less than
template <typename T> static bool eq ( T* a, T* b ) { return eq ( *a, *b ); } //equal
template <typename T> static bool eq ( T& a, T& b ) { return a == b; } //equal