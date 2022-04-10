#ifndef _STACK_H_
#define _STACK_H_
#include "../Chapter2_Vector/vector.h"

template <typename T> 
class Stack: public Vector<T> 
{
    public:
        void push(T const& e){Vector<T>::insert(Vector<T>::size(), e);}
        T pop() {return Vector<T>::remove(Vector<T>::size()-1);}
        T& top() {return (*this)[Vector<T>::size()-1];}
};

#endif