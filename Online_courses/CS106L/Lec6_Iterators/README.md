# STL Itreators

## Operations

Each container has its own iterator, but they have similar behavior!

```cpp
std::set<type> s = {0, 1, 2, 3, 4, 5};
std::set::iterator iter = s.begin();//this is the iterator

++iter; //at 1
* iter; //1
(iter != s.end()) //you can compare iterator's equality

auto second_iter = iter; // can be copied
```

The iterators of different containers can be sorted below:

![iterators](../../images/iterator.png)

***

**Why ++iter and not iter++?**

Ans: ++itre return the incremented value, itre++ return the previous value and then increments it(waste a little time.)

Generally speaking, i++ make a copy of this obj.

If you are confused, [here](https://isocpp.org/wiki/faq/operator-overloading#increment-pre-post-speed) is an FAQ maybe helpful.

## Cpp's for-each loop

```cpp
std::set<int> set{3, 1, 4, 1, 5, 9}; 
for (const auto& elem : set) {
  cout << elem << endl;
}

std::map<int> map{{1, 6}, {1, 8}, {0, 3}, {3, 9}}; 
for (const auto& [key, value] : map) {
  cout << key << ":" << value << ", " << endl;
}
```

## Iterator & Pointer

Iterator is a form of pointer, it also can be deferenced by `->`, for example:

```cpp
 
int x = 5;
int* pointerToInt = &x;// creates pointer to int
cout << *pointerToInt << endl;//5
std::pair<int, int> pair = {1, 2}; 
std::pair<int, int>* pointerToPair = &pair; 
cout << (*pair).first << endl; //1 
cout << pair->first << endl; //1
```


