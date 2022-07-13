# 数据类型

## 基本数据类型

`sizeof`后面对类型名必须加括号: `sizeof(int)`; 但对于变量名括号是可选的: `sizeof var`

初始化: 

```bash
int var(123);
int var = {12};
int var{12};
int var = {};
int var{}; # init as zero
```

char在默认情况下是否有符号是未定义的，看具体的c++实现。如果这点很重要，则可以手动加前缀。

`wchar_t`, 使用`wcin`, `wcout`处理`wchar_t`数据流。`char16_t, char32_t`使用前缀`u`与`U`表示, 二者都是无符号的。

`cout.setf(ios_base::fixed, ios_base::floatfield)`: ios_base::fixed表示：用正常的记数方法显示浮点数(与科学计数法相对应); ios_base::floatfield表示小数点后保留6位小数.

`%`运算只可以针对两个整形进行


C++类型转换:

> 将一种算数类型的值赋给另一种算数类型的变量时，C++对值进行转换
> 表达式中包含不同的类型时，C++将对值进行转换
> 将参数传递给函数时，C++将对值进行转换

初始化时, 当丢失精度或截断时会产生问题; {}初始化不允许narrowing

计算表达式时, 将bool, char, s/u char, short类型提升为int, which called 整型提升。if short 比 int 短, unsigned short转化为int; 若相同, 则unsigned short转为unsigned int.

不同类型进行计算时，小类型也会转换为大类型。[这是一个顺序](https://blog.csdn.net/qq_30534935/article/details/102393858)

c++强制类型转换也引入了多个算符: `static_cast<dst>(src)`

## 复合数据类型

### 数组

数组初始化规则:

```cpp
int cards[4] = {1,2,3,4};
int hand[4];
float ht[5] = {5.0,2.5};//对一部分初始化，其他设置为0
long totoals[22] = {0}; //全部初始化为0
short things[] ={1,2,3,4}; //Complier 会自动判断长度, 为4
hand[4] = {5,6,7,8}; // ERROR!!! 定义数组时才能使用初始化
hand = cards;        // ERROR!!! 不能将一个数组赋值给另一个

//c++11, News:
初始化时可省略=号
大括号可为空，全部设置为0
列表初始化禁止narrowing
```

### 字符串

C-style string:

以空字符'\0'结尾

```cpp
char dog[8] = {'b', 'e', 'a', 'u', 'x', ' ', 'I', 'I'};  // not a string
char cat[8] = {'f', 'a', 't', 'e', 's', 's', 'a', '\0'}; // a string
char bird[11] = "Mr.Cheeps";
char fish[]   = "Bubbles";
```

`cout`打印内容会遇到空字符才终止，所以第一种string会导致其他内存块被输出。
使用字符串常量可以隐式地包含空字符，且可以推断数组长度。

c++中任意两个由空白分隔的字符串常量都会自动拼接成一个

读输入的字符串时, 为了读入空格, 使用 cin.getline()与cin.get()区别在于前者会丢弃缓冲区中的换行符/而后者会保留换行符

`cin.getline(A,size).getline(B,size)`函数调用会返回一个`cin`对象, 可继续调用其成员函数。

**Why get() and getline()?**

> getline()使用上更方便, 但get()输入更加仔细: 可以通过判断下一个字符的内容来判断是因为数组空间而停止读入还是因为遇到换行符停止。

> 当遇到空行时, get()会读取后设置失效位, 可以使用`cin.clear()`恢复输入。

> 当输入字符串比分配空间长时, 则二者将把剩下字符留在输入队列中, getline()也会设置失效位, 关闭后面的输入。

> cin>>temp 后, 也会在缓冲区中留下一个换行符, 所以需要调用.get()成员函数后再调用他们

### String类

初始化: `string ss = {"test"}; string ss {"test"};`

可以将string 对象赋给另一个string 对象; 也可以使用`+`号将两个string对象合并起来。

可以使用getline(cin,str)来进行输入。

wchar_t, char16_t, char32_t 的字符串字面值分别使用: `L u U`前缀表示

C++11支持Unicode: 前缀u8; 支持raw字符串: 前缀R

### structure

结构体初始化: 

```cpp
structname s1=
{
    "name",
    info1,
    info2
};
sturctname s1 = {"name", info1, info2};
// c++11, not allow narrowing
sturctname s1 {"name", info1, info2};
sturctname s1 {}; // all zero
```

可以使用`=`对两个同类型结构体进行赋值，结构中每个成员都将设置为另一个结构中成员的值，即使是数组。底层实现是将按字节进行拷贝。

可以同时完成结构体定义与变量声明的过程:

```cpp
struct perks
{
    int key_num;
    char car[12];
} mr_glitz=
{
    7,
    "name"
};

// 匿名结构体
struct 
{
    int x;
    int y;
} position;
```

C++结构体除了成员变量外还可能有成员函数。

C++允许指定占用特定位数的结构成员:

```cpp
struct register
{
    unsigned int SN: 4; // 4bits for SN
    unsigned int :4;    // 4bits not used
    bool goodIn : 1;    // 1bit for goodIn
    bool goodTorgle:1;  // reverse val
}
```

### Union

能够存储不同的数据类型, 但只能同时存储其中的一种类型. 长度为最大成员长度. 用处在于当数据项使用多种格式且不会同时使用时，节省存储空间。

匿名共用体没有名称, 其成员将成为位于相同地址处的变量。每次只有一个成员是当前的成员。

### 枚举

`enum spectrum {red, orange, green, blue, violet, indigo, ultraviolet};`该语句将spectrum成为新类型:枚举; 将red orange等作为符号常量:0~7

且枚举只定义了赋值运算符, 没有定义算数运算。可以通过 `band = spectrum(3)`对枚举变量进行赋值。

若需要定义常量而不需要创建枚举类型的变量，则可以`enum {red, yellow, green};`

也可以显示赋值 `enum{one,one2 = 1, two = 2, eight = 8};`

枚举类型都有取值范围, 通过强制类型转换可以将范围内的任何整数值赋给枚举变量, 即使它不是枚举值。
取值范围是2的整数次幂

### 指针

指针是一个变量, 存储的是值的地址, 而非值本身。地址是指定量, 存储值为派生量. 可以使用`*`来进行解引用得到地址存储的值。

```cpp
int * temp;
*temp = 2233;
//ERROR!!! 程序只分配了存储地址的内存, 而并没有分配用来存指针所指向数据的内存
//初始化后不知道指针指向何处
```

不可以简单地将整数赋给指针: `int* pt; pt = 0xB8000000`; 应进行强制类型转换`pt = (int*)0xB8000000`.

**使用new来分配内存**

在运行时为一个int值分配未命名的内存, 并使用指针访问该值. `int* pn = new int;` 该块内存只能通过指针来进行访问, 说指针pn指向了一个数据对象. 

**使用delete释放内存**

当内存使用完成后, 将其归还给内存池. `int *ps = new int; delete ps;`将释放ps指针指向的那片内存, 不会删除ps指针本身. 可以将其指向新的内存空间。不能重复释放内存块, 也不能释放变量获得的内存.

动态数组: `int* psome = new int [10]; delete []psome;`, 同样可以使用`[0]`来访问数组元素. 数组名的值是不能改变的, 但指针值可以改变.

指针+1 = 指针+指向类型的字节数; 数组名为数组第一个元素的地址.

对数组应用sizeof得到数组长度, 对指针应用sizeof得到指针长度。

```CPP
short tell[10];
tell 等价于 &tell[0], tell+1 = tell + 2bytes
但&tell是这样的指针 short(*pas)[10], 即是一个指向10个elem的元素的指针.
&tell+1 = &tell + 20 byte
```

cout对于char数组/指针/字符串字面值都被解释为字符串第一个字符的地址，因此cout<< pt会输出字符串

c++有三种管理数据内存的方式: 自动存储/静态存储/动态存储

自动存储: 函数内部定义的变量使用自动存储空间, 在函数调用时产生/结束时消亡. 作用域为代码块

静态存储: 在函数外面定义变量; 在声明变量时使用关键字`static`

动态存储: 数据的声明周期完全不受程序的生存时间控制, 通过 `new`与`delete`控制

