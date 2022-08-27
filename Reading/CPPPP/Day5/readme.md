# 函数探幽

## 内联函数

compiler将使用相应的代码块替换函数调用, 执行会更快, 但可能会消耗更多内存(多个地方调用)

使用: `在函数声明前加上关键字inline, 在函数定义前加上关键字inline1`. 但声明不一定会让编译器这么做，当其调用自己/函数过大就不将其作为内联函数。

可以替换C的一些宏

## 引用变量

通过将引用变量作为函数参数, 函数将使用原始数据而非其副本。

```cpp
int rats;
int & rodents = rats; //rodents就是rats的引用变量(别名)
```
二者指向同一块内存

引用是不是很像指针？但还是有不同：

引用必须在声明时初始化, 而不能像指针一样可以分开进行。引用更像const指针, 一旦与一个变量关联起来就不能改变。

`int& rodents = rats; <==> int * const pt = &rats;`

将引用变量作为函数参数传递可以使用被调用函数访问调用函数的变量。

当希望程序使用函数传递的信息而不修改时, 应该使用常量引用`returntype func(const typename & ra);` 当数据比较大时, 引用是更快的相比值传递。

当实参与引用参数不匹配时, C++将产生临时变量, 其产生条件如下:

1. 参数为const引用  
2. 实参的类型正确，但不是左值 或 实参的类型不正确, 但可以被转换为正确的类型。

简言之, 只有在函数意图不是修改参数时(const), 才允许这样的转换。

应尽量使用const:

1. 使用const可以避免无意中修改数据的情况  
2. 使用const使函数能够处理const与非const实参, 否则只能接受非const数据  
3. 使用const引用能够使函数产生正确的临时变量  

C++11引入了新的`右值引用`, 使用两个`&&`表示:
```cpp
double && rref = sqrt(36.00);
double j = 15.0;
double && jref = 2.0 * j + 18.5;
```

引用非常适合用于结构和类, 实际上引用也是为了用于这些类型而不是基本内置类型。

返回引用: `dup = retref(one, two);`如果retref返回一个结构, 那么将把整个结构复制到一个临时位置, 再将这个拷贝复制给dup; 但在返回值为引用时, 直接把one复制到dup了，效率更高。

返回引用时注意: 

1. 避免返回指向临时变量的引用  
2. 使用new分配内存空间, 并返回改空间的引用时, 会隐藏调new的调用, 导致忘记delete, 内存泄漏。  

将const用于引用返回类型:

常规的函数返回值是右值, 因为其返回值存在临时内存单元中, 运行到下一条语句时可能不再存在。

增加const可以避免设计的模糊性

**对象, 继承与引用**

ofstream对象可以使用ostream类的方法, 这样使得特性从一个类传递给另一个类的语言特性称为继承, ostream是基类, ofstream是派生类, 派生类继承了基类的方法。

继承的另一个特征是, 基类引用可以指向派生类对象, 而无需进行强制类型转换:`定义一个接受基类引用作为参数的对象, 调用该函数时, 可以将基类对象作为参数, 也可以将派生类对象作为参数.` 例如参数类型为`ostream&`的函数可以接受`ostream对象或ofstream对象`作为参数。

何时使用引用参数？

使用引用的主要原因有两个: 1. 程序员能够修改调用函数中的数据对象 2. 通过传递引用而非整个数据对象可提高程序运行速度

对于传递值而不修改的函数:  
1. 如果数据对象很小, 按值传递  
2. 如果数据对象为数组, 使用const指针  
3. 如果数据对象是较大的结构, 使用const指针或const引用  
4. 如果数据对象是类对象, 使用cosnt引用。类设计的语义常常要求使用引用，这也是C++新增该特性的原因

对于修改函数中数据的函数:

1. 如果数据对象是内置类型, 则使用指针  
2. 如果数据对象是数组, 只能使用指针  
3. 如果数据对象是结构, 使用指针或引用  
4. 如果数据对象是类对象, 则使用引用

## 默认参数

当函数调用中省略了实参时自动使用的一个值, 例如`void wow(int n);`设置n为默认值=1，则函数调用时`wow()`相当于`wow(1)`. `left("thery",3);`设第二个参数默认值为1时，`left("test")`也不会报错。

通过这样设置默认值`char* left(const char* str, int n = 1);`

对于带参数列表的函数，必须从右向左添加默认值, 也就说, 要为某个参数设置默认值, 那么右边的参数都需要有默认值。

且只需要原型定义默认值即可，函数定义与没有默认参数时完全相同。

## 函数重载

C++允许定义名称相同的函数, 条件是其特征标不同: 参数的数目和/或参数类型不同, 则特征标不同。**注意，只有返回值不同的同名函数不算重载函数，会报错**

C++函数原型把类型引用和类型本身视作同一个特征标, 且有多个重载函数后, c++不会继续进行参数的强制类型转换，会直接报错。

当函数基本上执行相同的任务，但使用不同形式的数据时，才应该使用函数重载。另外使用默认参数也可以在一定程度上减少重载，但要注意`必须让编译器知道调用哪个函数, 省略默认参数时仍需要能辨别出来，否则会报错`。

C++给每一个重载函数进行名称修饰, 根据函数原型中的形参类型对函数名进行加密。

## 函数模板

C++使用泛型定义函数, 其中的泛型可以使用具体的类型(int/double)替换。

模板重载: 模板中不一定要全是模板类型, 且模板的函数特征标必须不同

模板的局限性: 赋值操作可能遇到数组类型; 比较操作可能遇到结构与数组名; 以及各复合类型的运算符。这些都是没有定义的。因此C++也允许了运算符重载。

**显示具体化**是解决上述问题的另一种途径:

```cpp
// normal func
void swap(job&, job&); 
// template func
template <typename T>
void swap(T&, T&);
// explicit specialization for job type
template <> void swap<job>(job &, job&);
template <> void swap(job&, job&);
```

具体化优先于常规模板, 非模板函数优先于具体化和常规模板

显式实例化与显式具体化的不同:

显式实例化: `template void swap<int>(int,int);`其意思是通过swap()模板生成int类型函数定义；

显式具体化: `template<> void swap<int>(int&,int&);其意思是不使用swap()模板生成函数定义, 而应该使用专门为int类型定义的函数定义。

区别在于`template`后是否有`<>`, 在同一文件中包含同一类型的实例化与具体化将报错。

强制实例化:

```cpp
template <typename T>
T Add(T a, T b)
{
    return a+b;
}
...
int m = 6;
double x = 10.2;
cout << Add<double>(x,m)<<endl;
```
这里的模板和函数调用Add(x,m)不匹配，因为模板要求两个参数的类型相同。但通过使用Add<double>(x,m)可以强制化为double类型实例化。将m强制转换为double类型。

但对`template<typename T> swap(T&, T&);`函数使用上述技巧，是不可以的。因为形参的类型为double的引用，不能指向int变量m。

**编译器选择使用哪个函数版本？**

编译器选择函数的过程称为重载解析, 分为以下三步:

1. 创建候选函数列表, 其中包含与被调用函数的名称相同的函数和模板函数  
2. 使用候选函数列表创建可行函数列表, 都是参数数目正确的函数. 为此有一个隐式转换序列, 其中包括实参类型与相应的形参类型完全匹配的情况。  
3. 确定是否有最佳的可行函数，如果有，则使用它; 否则函数调用出错

从最佳到最差的顺序如下:  
1. 完全匹配: 常规函数优先于模板  
2. 提升转换(char和short自动转换为int, float自动转换为double等)  
3. 标准转换(int转换为char, long转换为double等)  
4. 用户定义的转换, 如类声明中定义的转换  

但有时完全匹配函数有多个: 

进行完全匹配时, C++允许某些"无关紧要的转换": 引用/[]与*/函数名与函数指针/const/volatile

规则: 非const的数据指针和引用优先与非const指针域引用参数匹配。非模板函数优先于模板函数。如果两个完全匹配的函数都是模板函数, 那么较为具体的模板函数优先(显示具体化>隐式具体化)或编译器认为需要转换少的函数。

模板函数中也会有因为多个类型而无法确定中间变量类型的情况, C++提供了decltype()函数推断类型:
`decltype(x+y) m = x+y;` 

该函数使用一个核对表来判断类型:

1. 如果expression是一个没有用括号括起来的标识符, 则var的类型与该标识符类型相同  
2. 如果是一个函数调用, 与函数返回类型相同  
3. 如果是一个左值, 则var是指向其类型的引用, 且expression必须背括号括起来  
4. 如果都不满足, 那么与其类型相同  

但无法推断模板函数返回值？C++11的后置返回类型:

```cpp
double h(int x, int y); 
// 可以写成
auto h(int x, int y) -> double;
// 将返回类型移动到了参数声明后面
template <class T1, class T2>
auto gt(T1 x, T2 y) -> decltype(x+y)
{
    ...
}
```

