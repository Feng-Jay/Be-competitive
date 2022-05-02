# Classes

Containers are all the classes defined in the STL.

**Classes can provide their users with public interface and seperate this from a private implementation.**

## Public/Private section

Public section:

* User can access anything here.

* Define interface for interacting with the private member variables!

Private section:

* Contains almost all member variables.

* User can not access or modify anything here.

## Namespace

It is used for avoid name clashes, and each class has its own namespace, which can be called:

```cpp
namespace_name:: name
```

## this KeyWord

```cpp
void Student::setName(std::string name){
	name = name; //huh? 
}
```
This is wired! Change to :

```cpp
 
void Student::setName(string name){ 
	this->name = name; //better!
}
```

`this->elem_name` means the item in this Classes' object with name elem_name. To reduce naming conflicts.

## Constructor

Used to initialized the member variables of an object.

Has the same name of the Class, will be executed everytime when you create a object. 

Can be overloaded.

## Destructor

When we are done using our array, we need to delete [] it.

```cpp
//int * is the type of an array variable 
int *my_int_array;
//this is how you initialize an array
my_int_array = new int[10];
//this is how you index into an array 
int one_element = my_int_array[0]; 
delete [] my_int_array;
```
delete always happen in the destructor of a class. 

The Destructor is defined using `Class_name::~Class_name()`. It will not be called explicitly, it will be called when the object out of scope.

## Template Class

When you use containers in STL, for example, `vector`. It should be able to contain any data type(int,double,...,my_classes). 

How to realise this?

**Template classes!!!**

It is a class that is parametrized over some number of types. A class that is comprised of member variables of a general type/types.

Almost all containers are `Template class`.

```cpp
template<class First, class Second> class MyPair { public:
		First getFirst(); 
		Second getSecond();
		/*...*/
		void setFirst(First f);
		void setSecond(Second f);
	private:
		First first;
		Second second;
};
```
Use generic typenames as placeholders.

When you using template class, **include 'class.cpp' in 'class.h'.** Templates don’t emit code until instantiated
, so include the .cpp in the .h instead of the other way around!