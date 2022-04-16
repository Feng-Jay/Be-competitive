#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "../Chapter3_List/list.h"

template <typename T>
class Queue : public List<T>{
    // size() can be reused
    // empty() can be reused
public:
    void enqueue(T const& e){List<T>::insertAsLast(e);}
    T dequeue(){ return List<T>::remove(List<T>::first());}
    T& front(){return List<T>::first()->data;}
};


#endif