# Struct binding

```cpp
auto p = std::make_pair("s",5);
auto [a, b] = p;
<=-------------equal-to-------------=>
string a = p.first;
int b = p.second;
```
Works for regular stucts, too. 
**But, no nested structed binding!!!**

# References

Give an alias to a named variable. All the modifies on the reference will take effect on the origin one.

In cpp, `=` default makes a copy.

You can not set a reference to a rvalue:

```cpp
int & ref = 1; //this is wrong!
```

# Const & Const References

If it is a const variable, you can't modify it:

```cpp
std::vector<int> vec{1, 2, 3};
const std::vector<int> c_vec{7, 8}; // a const variable std::vector<int>& ref = vec; // a regular reference 
const std::vector<int>& c_ref = vec; // a const reference

vec.push_back(3); // OKAY 
c_vec.push_back(3); // BAD - const 
ref.push_back(3); // OKAY 
c_ref.push_back(3); // BAD - const
```
**Can not declare non-const ref to const vector.**

## const and auto

```cpp
std::vector<int> vec{1, 2, 3};
const std::vector<int> c_vec{7, 8};
std::vector<int>& ref = vec;
const std::vector<int>& c_ref = vec;
<=---------------------------------=>
auto copy = c_ref; // simple copy
const auto copy = c_ref; //const copy
auto & a_ref = ref; //simple reference
const auto & c_aref = ref; //const reference
```

Seeing that auto will ignore the const and reference, we should add the keywords when needed.










