#include "vector.h"

using std:: cout; using std:: endl;

template <typename T>
void print(T& i){
    cout<< i <<" ";
}

template <typename T>
void plus1(T& i){
    i+=1;
}

int main(){
    int mylist[5]= {1, 9, 7, 3, 8};
    Vector<int> my(mylist,5);
    void (*show)(int&) = print;
    void (*p1)(int&) = plus1;
    my.traverse(p1);
    my.traverse(show);cout<<endl;
    // cout << my.size()<<endl;
    // cout << my.disorder()<<endl;
    cout << my.find(10)<<endl;
    my.insert(4,11);
    int temp =12;
    my.insert(temp);
    my.insert(13);
    my.insert(14); my.insert(15);my.insert(16);
    my.traverse(show);cout<<endl;
    my.remove(0,3); my.remove(0);
    my.traverse(show);cout<<endl;
    my.sort();
    my.traverse(show);cout<<endl;
    cout<<my.search(13)<<endl;
    my.unsort();
    my.traverse(show);cout<<endl;
    cout<<my.find(13)<<endl;

    my.insert(13);
    my.sort();
    my.traverse(show);cout<<endl;
    my.uniquify();
    my.deduplicate();
    my.traverse(show);cout<<endl;
}