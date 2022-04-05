#ifndef _VECTOR_H1_
#define _VECTOR_H1_
#include <iostream>
#include <stdlib.h>
#include <algorithm>

typedef int Rank;
const int DEFAULT_CAPACITY = 3;

template <typename T> 
class Vector{
    protected: 
        Rank _size; int _capacity; T* _elems;
        void copyFrom(T const* A, Rank lo, Rank hi); // copy A[lo,hi)
        void expand(); // expand space
        void shrink(); // compress

        bool bubble(Rank lo, Rank hi);// scan and swap
        void bubble_sort(Rank lo, Rank hi); 
        
        Rank max(Rank lo, Rank hi); //select max elem's rank
        // void selectionsort(Rank lo, Rank hi);

        void merge(Rank lo, Rank mi, Rank hi);
        void mergesort(Rank lo, Rank hi);

        // Rank partition(Rank lo, Rank hi); 
        // void quicksort(Rank lo, Rank hi);

        // void heapsort(Rank lo, Rank hi);

    public:
        //constructors
        Vector();
        Vector(T const* A, Rank n); 
        Vector(T const* A, Rank lo, Rank hi);
        Vector(Vector<T> const& V); 
        Vector(Vector<T> const& V, Rank lo, Rank hi);

        //destructor
        ~Vector();

        //read-only api
        Rank size() const;
        bool empty() const;
        int disorder() const;
        Rank find(T const& e) const;
        Rank find(T const& e, Rank lo, Rank hi) const;
        Rank search(T const& e) const;
        Rank search(T const&e, Rank lo, Rank hi) const;

        //writable api
        T& operator[](Rank r) const;
        Vector<T>& operator= (Vector<T> const&);
        T remove(Rank r);
        int remove(Rank lo, Rank hi);
        Rank insert(Rank r, T const& e);
        Rank insert(T const& e); //insert as the last elem
        void sort(Rank lo, Rank hi);
        void sort();
        void unsort(Rank lo, Rank hi);
        void unsort();
        int deduplicate(); //unsort dedup
        int uniquify(); //sort unify
        
        // travel
        void traverse(void(*) (T&)); 
        // template <typename VST> void traverse(VST&);
};
#include "vector.cpp"
#endif