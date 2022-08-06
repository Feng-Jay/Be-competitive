# 类

> "轻松地使用这种语言. 不要觉得必须使用所有的特性, 不要在第一次学习时就试图使用所有的特性"

## 运算符重载

一种形态的C++多态. 之前函数重载的作用就是使用 **同名函数处理不同数据类型**, 运算符重载将这种思想扩展到运算符上. 

*\*号在两个数字之间是乘积, 在地址前是取地址*

需要重载运算符, 需要使用如下的运算符函数的特殊函数格式:

```cpp
operator+(argument-list) // reimplement +
{...}
//example
sum = data1 + data2;
    = data1.operator+(data2);
```

**限制**

> 1. 重载后的运算符必须至少有一个操作数是用户定义的类型.
> 2. 使用运算符时不能违反原来的句法规则, 不能修改运算符的优先级
> 3. 不能创建新运算符
> 4. 不能重载 `sizeof` `.` `.*` `::` `?:` `typeid`(一个RTTI运算符), `const_cast` `dynamic_cast` `reinterpret_cast` `static_cast`(强制类型转换运算符)
> 5. `=`, `()` `[]` `->`只能通过成员函数进行重载, 其他运算符可以通过成员/非成员函数进行重载 对于只有二元形式的运算符只能重载为二元运算符(运算符也是函数实现的)

## 友元

对于对象的私有部分的访问目前只能使用公有类方法这种途径, 友元的提出可以拓展这条道路.

友元分为: 友元函数, 友元类, 友元成员函数

友元函数: 让函数成为类的友元, 可以让该函数与类成员函数有相同的访问权限.

例如下面这种问题:

```cpp
// 运算符重载
A = B * 1.25; <==> A = B.operator*(1.25); //这样写肯定没错
// 但如果有人这么写呢?
A = 1.25 * B; // 一般使用非成员函数来重载运算符.
//非成员函数不是由对象调用的, 所有值都是显式参数
Time operator* (double m, const Time& t);
```

这就引出了一个问题: **非成员函数不能直接访问类的私有数据**, 使用友元函数可以解决

**1. 创建友元**

首先将其原型放在类声明中, 并在原型前加上关键字`friend`

```cpp
friend Time operator* (double m, const Time& t);
```

意味着: 

1. 该函数在类声明中声明, 但不是成员函数, 不能使用成员运算符来调用

2. 虽然不是成员函数, 但权限与成员函数相同

另外在实现函数定义时, 不要使用`Time::`限定符, 也不需要使用`friend`

最常用的重载: `<<`运算符, 配合cout输出类对象:

两种思路: 1. 修改iostream, 让cout有Time类函数 2. Time类声明, 知道如何使用cout. 后者无疑更优.

要使Time类知道cout 必须使用友元函数:

```cpp
cout << trip;
```

cout 是一个 ostream类对象, 因此 trip对象是第二个被调用的参数, 如果不使用友元函数, 那就变成了 `trip << cout;`有些奇怪, 需要交换了一下操作数顺序.

```cpp
cout << trip;
void operator<<(ostream & os, const Time & t)
{
  os << t.hour << "hours, " << t.minutes << " minutes";
}
```

可以看到, 上述函数并不需要成为 ostream的友元, 因为他只将ostream对象作为整体使用, 不使用其内部成员. 所以必须是Time的友元, 而不需要是ostream的友元.

但上述重载不允许`cout<<"ttt"<<trip;`这样的操作

需要修改返回值为ostream对象:

```cpp
ostream& operator<<(ostream & os, const Time & t)
{
  os << t.hour << "hours, " << t.minutes << " minutes";
  return os;
}
```

## 类的自动转换与强制类型转换

内置类型转换, 例如:

```cpp
long count = 8; // int 2 long
double time = 11; // int 2 double
int side = 1.33;  //double 2 side
```

C++将上述内容都看做数字, 可以相互转换

但C++不会自动转换不兼容类型:

```cpp
int * p = 10; // ERROR!!!
int * p = (int *) 10; //Correct!!!
```

在概念上整数与指针完全不同, 但仍可以通过强制类型转换实现.

**可以将类定义为与基础类型/另一个类 相关, 从而使从一种类型转换为另一种类型是有意义的**

在C++中, **接受一个参数的构造函数是类型与参数类型之间转换的模板, 或多个参数但后面都有默认值**

```cpp
Stonewt:: stonewt(double lbs){...} 
Stonewt temp(123.1); <==> Stonewt temp; temp = 123.1;
```

在函数参数与返回值时也可以使用

但这样的操作也会导致意外, 使用关键字`explicit`关闭该特性

```cpp
explicit stonewt(double lbs){...} 
Stonewt temp;
temp = 123.1; // Not valid
temp = Stonewt(123.1);//Ok
temp = (Stonewt)123.1;//Ok
```

**转换函数**

可以将double等类型转换为Stonewt对象, 那是否可以反过来, 将Stonewt对象转换为double值?

需要使用转换函数: 强制类型转换

```cpp
operator typeName(){...}
```

注意点:

* 转换函数必须是类方法(通过类对象调用)
* 转换函数不能指定返回类型(不需要)
* 转换函数不能有参数

即需要将转换函数添加到类声明中去:

```cpp
class Stonewt{
  ...
  operator double() const;
  operator int()    const;
}
Stonewt:: operator double() const
{...}
Stonewt:: operator int() const
{...}
```

