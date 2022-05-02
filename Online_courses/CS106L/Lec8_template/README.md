# Template Classes

## Member Types

Sometimes, we need a name for a type that is indepent on our template types. For example:

```cpp
std::vector::iterator it = a.begin();
```

iterator is a member type of vector.

When using it in a class interface, be careful, it defines a nested type:

```cpp
//vector.h
template<typename T> class vector {
   using iterator = ...  // something internal
private:
   iterator front;
}

//vector.cpp
template <typename T>
iterator vector<T>::insert(iterator pos, int value) {...}
//ERROR! iterator is a nested type in namespace vector<T>::

//vector.cpp
template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos, int value) {...}
```

## Template classes

- Add `template<class T1, T2,...>` before class definition in `.h` 

- Add `template<class T1, T2,...>` before all function signatures in `.cpp`

- When returning nested types (like iterator types), put `typename ClassName<T1, T2..>::member_type` as return type, not just `member_type`.

- Templates don’t emit code until instantiated, so #include the `.cpp` file in the `.h` file, not the other way around!
 

## Const & Const References/Classes

**Why const?**

`const` may enable the compiler to optimize and helps your peers understand how your code is intended to be used (and the compiler will catch possible misuse).

Look this example:

```cpp
//main.cpp
std::string stringify(const Student& s){
	return s.getName() + " is " + std::to_string(s.getAge()) + " years old." ;
}
//compile error!
```
Compiler doesn't know `getName` and `getAge` don't modify `s`. We need to promise this by defining them as `const function`.

**Add const to the end of function signatures!**

const ClassName can only use const interface.

## Nitty Gritty

**const iterator and const_iterator**

```cpp
using iterator = std::string*;
using const_iterator = const std::string*;
const iterator it_c = vec.begin(); 
//string * const, const ptr to non-const obj *it_c = "hi"; //OK! it_c is a const pointer to non-const object
it_c++; //not ok! cant change where a const pointer points!
const_iterator c_it = vec.cbegin(); 
//const string*, a non-const ptr to const obj c_it++; 
// totally ok! The pointer itself is non-const
*c_it = "hi" // not ok! Can’t change underlying const object
cout << *c_it << endl; 
//allowed! Can always read a const object, just can't change
//const string * const, const ptr to const obj
const const_iterator c_it_c = vec.cbegin();
cout << c_it_c << " points to " << *c_it_c << endl; 
//only reads are allowed!
```

- const iterator = cannot increment the iterator, can dereference and change underlying value

- const_iterator = can increment the iterator, cannot dereference and change underlying value

- const const_iterator = cannot increment iterator, cannot dereference and change underlying value



