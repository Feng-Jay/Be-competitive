# What's in STL?

* Containers
* Iterators
* Functions
* Algorithms

## Sequence Containers

### vector

**size** = number of elements in a vector 

**capacity** = amount of space saved for a vector

### deque

可以高效地访问任何一个元素，且可以高效插入删除头尾元素，也叫双端队列。

### list

可以快速地随机插入，但不能随机访问

### How to choose!

![image-20220311172340783](/Users/ffengjay/Library/Application Support/typora-user-images/image-20220311172340783.png)

![image-20220311172457360](/Users/ffengjay/Library/Application Support/typora-user-images/image-20220311172457360.png)

## Container Adaptors

Container adaptors provide a different interface for sequence containers.

可以选择底层的container是什么比如：

![image-20220311173049731](/Users/ffengjay/Library/Application Support/typora-user-images/image-20220311173049731.png)

限制了一些操作。

![image-20220311173537050](/Users/ffengjay/Library/Application Support/typora-user-images/image-20220311173537050.png)

可以通过这样的声明来更换内部的template

## Associative Container

关联性容器：

**Ordered**

* set (unique elements)
* map (k-v pairs)

**Unordered**

- { } unordered set
- { : } unordered map 

STL map真的会存放pairs

![image-20220311174055677](/Users/ffengjay/Library/Application Support/typora-user-images/image-20220311174055677.png)

迭代：

map 使用了 std::pair, 所以可以使用结构体绑定进行访问。

```cpp
 
std::set<...> s; 
std::map<..., ...> m;
for (const auto& element : s) { 
  // do stuff with element
}
for (const auto& [key, value] : m) { 
  // do stuff with key and value
}
```

set 和 map数据结构必须给出定义的比较符(`<`)

对于非有序的set和map来说，它们需要一个hash function而不是定义的比较符<

且其一般比有序版本快



