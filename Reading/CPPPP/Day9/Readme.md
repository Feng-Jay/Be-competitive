# 类与内存动态分配

**静态类成员的特点: 无论创建多少对象, 程序都只创建一个静态类变量副本**

不能在类声明中初始化静态成员变量, 因为声明描述了如何分配内存, 但并不分配内存.(除非为const/enum)

**构造函数使用new分配内存时, 必须在相应的析构函数中使用delete释放内存**

C++自动提供的成员函数:

> * 默认构造函数,如果没有定义构造函数
> * 默认析构函数, 如果没有定义析构函数
> * 复制构造函数, 如果没有定义
> * 赋值运算符, 如果没有定义
> * 地址运算符, 如果没有定义

前面两种之前都接触过, 地址运算符也是返回调用对象的地址, 我们主要看中间那两个:

**复制构造函数**

```cpp
Class_name(const Class_name&);
```

接受一个指向类对象的常量引用作为参数.

当新建一个对象并将其初始化为同类现有对象时, 复制构造函数都会被调用.

```cpp
// motto is a StringBad object
StringBad ditto(motto);
StringBad metto = motto;
StringBad also  = StringBad(motto);
StringBad * p   = new StringBad(motto);
```

上述情况下都会调用复制构造函数. **每当程序生成了对象副本, 编译器都将使用复制构造函数**

**当函数按值传递对象或返回对象时, 就会创造原始变量的一个副本, 使用复制构造函数. 生成临时对象时也会: 将三个vector相加, 可能生成一个临时的vector存储中间结果.**

为什么会导致程序出错呢? 我们看他的功能:

```cpp
//就是将逐个复制非静态成员, 浅copy
StringBad sailor = sports;
//<==>
StringBad sailor;
sailor.str = sports.str;
sailor.len = sports.len;
```

因此导致问题的原因就浮出水面了:

* 当类中有静态成员变量的时候, 不会更新其内容
* 中间成员变量会释放掉指针指向内容, 导致内存多次释放.

**解决方案自定义一个显式的复制构造函数解决问题: 变成深copy**

***

**赋值运算符**

```cpp
Class_name & Class_name:: operator=(const Class_name &);
//接受并返回一个类对象的引用.
```

赋值运算符的功能及何时使用:

与复制构造函数类似, 隐式实现也是对成员进行逐个复制, 静态数据成员不受影响.

```cpp
StringBad headline1("test");
StringBad knot;
knot = headline1;
//-----------------------------------//
//初始化对象时不一定会使用
StringBad metoo = knot;
//根据不同的实现, 可能会使用copy构造函数一步完成;也可能使用copy构造函数创建一个临时对象, 然后使用=运算符
```

也是由于浅copy导致的问题. 同样定义一个赋值运算符来解决, 要点如下:

> * 由于目标对象可能引用了之前分配的数据, 需要delete[]释放旧数据
> * 函数应该避免将对象赋给自身, 否则可能会删除对象内容.
> * 函数返回一个对象的引用

```cpp
S1 = S2 = S3; <==> S1.operator=(S2.operator=(S3));
```

***

*C++空指针: C中0代表数字0与空指针, 也可以使用(void\*) 0 来标记空指针, C++11提供了`nullptr`来表示空指针*

静态成员函数:

* 不能通过对象调用静态成员函数, 也不能使用this指针. 可以使用类名+作用域解析符来调用.
* 静态成员函数不与特定对象关联, 因此只能使用静态数据成员, 不能访问其他成员.

## 构造函数使用new的注意事项

* 构造函数用new, 析构必须有delete, new[] 对应 delete []
* 有多个构造函数, 必须相同的方式new(全带[], 或全不带[]), 因为只有一个析构函数, 所有析构函数都必须与其兼容. 可以一个构造函数中new初始化指针, 另一个构造函数中初始化为空指针, 这是允许的.
* 定义一个复制构造函数, 进行深度复制, 例如:

```cpp
String::String(const String& st)
{
  num_string++;
  len = st.len;
  str = new char [len + 1];
  std::strcpy(str, st.str);
}
```

* 定义一个赋值运算符, 通过深度复制将对象复制给另一个对象, 例如:

```cpp
String& String::operator=(const String& st)
{
  if (this == &st) return *this;
  delete [] str;
  len = st.len;
  str = new char [len + 1];
  std::strcpy(str, st.str);
  return *this;
}
```

## 返回对象的说明

我们可以返回: 对象的引用, 指向对象的const引用/cosnt对象

**返回const对象的引用**

使用原因: 提高效率, 一般是参数被声明为const 引用, 因此返回也是const引用, 这样才匹配

**返回非const的引用**

重载赋值运算符, cout一起使用的<<算符: 前者是提高效率, 后者则必须这么做

```cpp
String s1("Good stuff");
cout<<s1<<" is coming";
```

operator<<(cout, s1)的返回值是一个现实"is coming"的对象, 返回类型必须是ostream&, 因为如果返回ostream将要求调用ostream的复制构造函数, 而起没有公有的复制构造函数.

**返回对象**

返回函数中的局部变量. 包含使用复制构造函数的开销, 无法避免.

**返回const对象**

例如之前的operator+会有这样的例子:

```cpp
net = float1 + float2;
float1 + float2 = net;
cout <<(float1 + float2 = net).megval()<<endl;
```

三种代码都是可行的, 都是float1+float2创造一个临时对象, 语句1中该临时对象赋给net, 语句2中net被赋给临时变量.

为了防止这种滥用, 可以 **将返回值改为 const类型的**, 这样只有语句1可用

## 指向对象的指针

