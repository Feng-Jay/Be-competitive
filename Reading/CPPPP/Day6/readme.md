# 内存模型与namespace

C++使用四种不同的方案存储数据, 区别在于数据在内存中驻留的时间: 

1. 自动存储持续性: 函数定义中声明的变量(包括函数参数)其存储持续性为自动的, 在代码块执行结束后释放
2. 静态存储持续性: 函数定义外定义的变量和`static`定义的变量的存储持续性为静态的，在程序整个持续运行过程中都存在
3. 线程存储持续性: 生命周期与线程一样长
4. 动态存储持续性: new分配的内存一直存在直到被delete。

同时也有作用域和链接性两个定义:

作用域: 名称在多大范围内可见。链接性: 描述名称如何在不同单元共享。

存储持续性+作用域+链接性 三者共同组成了C++的存储方式的特征

## 自动/静态/动态变量的存储方式

1. 在函数中声明的参数与变量的存储持续性为自动, 作用域为局部, 无链接性。存储在栈上面

2. 静态持续变量: 有三种链接性：外部/内部/无链接性. 这些变量在整个程序执行期间一直存在.如何声明三种链接性: 1在函数外声明/2在函数外生命并使用`static`关键字/3在函数内声明并使用`static`关键字.虽然变量一直存在, 但并不意味着作用域是全局的.

   **静态变量默认零初始化**支持常量表达式(与前者共称静态初始化)与动态初始化: 静态初始化意味着编译器处理文件时初始化变量/动态初始化意味着变量在编译后初始化

   无链接性的静态变量只在启动时初始化一次, 以后调用函数时不会再次初始化(很不一样哦)

   ```cpp
   //存储说明符
   auto
   register//显式声明自动变量
   static
   extern
   thread_local
   mutable// 即使struct or class是const, 其中某个成员也可以被修改
   //cv-限定符
   const    // 全局cosnt的链接性是内部的, 因为一般放在头文件中, 但也可以强加extern来声明为外部链接
   volatile // 即使程序代码没有对内存单元进行修改, 其值也可能变化, 防止编译器优化
   //函数链接性
   函数默认外部链接性
   可使用static关键字将其声明为内部的
   ```

3. 动态变量

   new算法初始化: `int *pi = new int (6);` 可以在new时初始化. 

   new失败时 将引发`std::bad_alloc`异常

   运算符new / new[] 分别调用以下函数: 

   `void* operator new(std:: size_t);`

   ` void* operator new[](srd::size_t); `

   是两个运算符重载, std:: size_t 是一个 typedef: `int *pi = new int; <==> int *pi = new(sizeof(int))`

   new也可以选择分配的空间, 叫做定位new运算符, `p1 = new (buffer) string;`

## 名称空间

声明区域: 可以在其中进行声明的区域

潜在作用域: 从声明点开始到其声明区域的结尾.(比声明区域小)

C++中, 每个声明区域都可以声明名称, 这些名称独立于其他声明区域中声明的名称:

```cpp
namespace Jack{
  double pail;
  void fetch();
  int pal;
  struct Well{...};
}
```

名称空间可以是全局的, 也可以位于另一个名称空间中, 但不能位于代码块中. 默认情况下, namespace具有外部链接性.

可以通过如下方法向namespace中添加代码:

```cpp
namespace Jack{
  void fetch()
  {
    ...
    // add the implement
  }
}
```

using 声明和 using 编译指令:

using声明时好像声明了相应的名称, 如果某个名称已经在函数中声明了, 则无法用using声明导入相同的名称.

而using编译指令在这种情况下将进行名称解析, 会进行变量的隐藏等内容.

一般使用using 声明更安全.

*#include将支持命名空间的库函数导入时, 会将其放入到命名空间std中*

***

命名空间也支持嵌套和使用using指令:

```cpp
namespace myth
{
  using Jill::fetch;
  using std::cout;
  using std::cin;
}
cin >> myth::fetch; <==> cin >> Jill::fetch;
```

可以创建别名:

```cpp
namespace mvft = my_very_favorite_things;
```

利用这个简化对嵌套命名空间的使用

匿名命名空间 <==> static的静态全局变量

且using声明只使用名称, 不需要指出函数的返回类型和函数特征等内容. 如果函数被重载, 将一次导入所有的版本.



名称空间的用途:

```
* 使用在已命名的名称空间中声明的变量, 而不是用外部全局变量/静态全局变量
* 如果开发了一个函数库/类库, 将其放在一个名称空间中
* 仅将using编译指令作为一种将旧代码转换为使用名称空间的权宜之计
* 不要在头文件中使用using编译指令.
* 导入名称时, 首选使用作用域解析运算符或using声明的方法
* 对于using声明, 首选将其作用域设置为局部
```

