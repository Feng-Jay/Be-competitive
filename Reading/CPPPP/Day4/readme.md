## 分支语句

<cctype>库中包含`isalpha(), isdigits(), isspace(), ispunct()...`来测试字符是否为对应的字符。

当发生输入类型不匹配时`int n; cin>>n;`会发生以下四种情况:

1. n的值保持不变

2. 不匹配输入会被保留在输入队列中

3. cin对象中有一个错误标记被设置

4. 对cin方法的调用将返回false

可使用如下方法继续输入:

```cpp
while(!(cin>>num[i]))
{
    cin.clear()
    while(cin.get()!='\n') continue;
    cout<<"please enter a number: ";
}
```

## 文件IO

假设有`35.8 19.2`这样的输入

`char ch; cin >> ch;`: ch = '3'

`int n;   cin >> n; `: cin一直读到非数字字符, n=38

`double x; cin>> x;` : cin一直读到不属于浮点数的字符, x = 38.5

`char word[50]; cin>>word;`: cin一直读到空白字符, word = "38.5"

`char word[50; cin,getline(word,50);`: cin一直读到换行符.

对于输入: 整数被转换为数字字符序列, 浮点数被转换成数字字符与其他字符序列, 字符数据不需要转换。

**写入到文本文件**

> 必须包含头文件fstream  
> fstream定义了一个用于处理输出的ofstream类  
> 需要声明一个/多个ofstream变量  
> 指明命名空间std;  
> 需要将ofstream对象与文件关联起来, 使用open()方法  
> 使用完文件, 使用close()方法  
> 可以使用ofstream对象与`<<`输出各种类型的数据

可以使用cout可用的任何方法。

**读取文本文件**

> 必须包含fstream  
> fstream定义了一个用于处理输入的ifstream类  
> 需要声明一个/多个ifstream对象  
> 指明命名空间std  
> open()关联文件, 使用完文件后, 使用close()关闭  
> ifstream对象与`>>`读取各种类型数据  
> ifstream 与get()方法读一个字符; getline()方法读一行; 可结合eof(),fail()等方法判断输入是否成功  
> ifstream对象本身用做测试条件时, 如果最后一个读取操作成功, 那么为true

检测文件是否成功打开 `is_open()`方法

## 函数

C++对于返回值类型有限制: 不能是数组, 但可以是其他任何类型(可以将数组作为结构体的部分来返回)

**为什么需要原型**

原型描述了函数到编译器的接口, 将函数的返回值类型以及参数的类型和数量告诉compiler. 否则一是会导致编译器效率不高, 二是有时函数可能不在文件中, 多个文件编译后链接起来。不指定参数列表的protype`void func(...);`通常仅当接受可变参数的C函数交互时才需要这样做。

函数与数组:

C++中，当用于函数头/原型时, `int* arr 与 int arr[]`含义相同。`int arr[]`提醒arr不仅指向int, 还是int数组的第一个int. 

传递常规变量时, 函数使用变量的拷贝; 但传递数组时, 函数使用原来的数组。


`const int* pt = &age; ` pt指向一个const int, 即*pt的值为const, 不能修改. 且const变量的地址只能分配给`const type* pt`, 不能分给非const指针。

一级间接关系时, 将非const指针赋给const指针是可以的: `int* pd = &age; const int* pt = pd;`

两级间接关系时, 不可以:

```cpp
const int** pp2;
int* p1;
const int n = 13;
pp2 = &p1;
*pp2 = &n;
*p1 = 10;
```
如果上述代码成立，则可以通过p1来修改const数据。

`int * const ps = &age;` 该const不能修改指针的值. 所以根据const位置的不同 *pt 与pt分别为const的。

**函数与二维数组**

`int data[3][4] = {{...},{...},{...}};`  
函数原型的参数该怎么写呢？  
`int sum(int (*arr)[4], 3);`或者 `int sum(int arr[][4],3);`  
上述两个原型都指出, arr是指针而不是数组. 且指针类型中指出了列数。  

**函数与结构**

函数按值传递结构有一个缺点: 若结构非常大, 则复制结构将增加内存要求，降低运行速度。C++可以通过传递指针/传递引用来实现。

使用array对象时与结构类似, 可以使用值传递, 也可以传递指针。

使用引用参数可以同时满足效率与表示的需求。

## 函数指针

函数也有地址: 存储器机器代码的内存的开始地址. 即只使用函数名即可

`double pam(int)`这样的函数原型对应的函数指针为`double (*pf)(int)`, 使用时`pf = pam`即可。

使用(*pf)时只需要将其看作函数名即可:

```cpp
double pam(int);
double (*pf)(int);
pf = pam;
double x = pam(4);
double y = (*pf)(5);
//实际上下面的方法也可以
double y = pf(5);
```

使用`typedef`进行简化:`typedef const double* (*p_fun)(...);` 然后就可以使用`p_fun p1 = f1;`来使用函数指针了。



