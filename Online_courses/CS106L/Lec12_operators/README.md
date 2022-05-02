# Operator overloading

## member functions

Add a function called operator_ to the class:

```cpp
class Time{
    bool operator < (const Time& rhs) const;
    bool operator + (const Time& rhs) const;
    bool operator ! () const; // unary, no arguments
}
// lhs is the this pointer
<=============================>
//usage 
Time a, b;
if (a.operator<(b)) {
 // equivalent to a < b
}
```

By using this method, operators can only be called on the left hand side. 

And its contend is settled.

## Non-Member function

Add a function named operator _ outside of class.

```cpp
bool operator < (const Time& lhs, const Time& rhs); 
Time operator + (const Time& lhs, const Time& rhs);
Time& operator += (const Time& lhs, const Time& rhs); 
Time operator ! (const Time& lhs, const Time& rhs);
```

pass both lhs and rhs values.

STL prefer this way, the lhs can be a non-class type.

Non-Member function is stated as a friend function of Class to  access its private variables. 

Rules:

1. Meaning should be obvious.

2. Should be similar to corresponding arithmetic operations. 

