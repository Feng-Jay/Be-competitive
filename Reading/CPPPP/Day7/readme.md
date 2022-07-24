# 对象与类

OOP的特性: 

* 抽象
* 封装与数据隐藏
* 多态
* 继承
* 代码的可重用性

OOP与过程性编程的区别:

1. 过程性编程首先要考虑遵循的步骤, 然后考虑如何表示数据
2. OOP编程首先考虑数据(如何表示数据+如何使用数据), 从用户角度考虑对象, 描述对象所需要的数据以及描述用户交互使用的操作. 完成这些后确定如何实现接口与数据存储.

## 抽象与类

指定类型确定了什么?

1. 决定数据对象需要的内存数量
2. 决定如何解释内存中的位
3. 决定可使用数据对象执行的操作或方法(对于内置类型, 有关操作信息被内置在编译器中, 但定义自己类型时必须提供这些信息)

访问控制:

使用类对象的程序可以直接访问public部分, 但只能通过公有成员函数(或友元函数)访问对象的私有成员. **公有成员函数是程序和对象的私有成员之间的桥梁**

防止程序直接访问数据称为**数据隐藏**, 类设计将公有接口与实现细节分开成为**封装**.

C++类成员的默认类型为private; C++结构也增加了如上特性, 区别是结构成员的默认类型为public

常用类来实现类描述, 而把结构限制为只表示纯粹的数据对象

### 实现类成员函数

* 定义成员函数时, 使用`::`标识函数所属的类
* 类方法可以访问类的`private`组件

```cpp
void Stock::update(double price)
{...}
```

因此该方法具有类作用域, 且stock类的其他成员函数也不必使用作用域解析运算符就可以使用update方法. 

也可以在类声明文件外定义内联函数:

```cpp
class Stock
{
  private:
  void set_tot();
};
inline void Stock:: set_tot()
{
  ...
}
```

内联函数要求在每个使用他的文件中都对他进行定义, 确保内联函数可用的最简便的方法就是: 将内联函数的定义放在定义类的头文件中.

其实根据改写规则, 类声明中定义方法 <==> 用原型替换方法定义, 然后再类声明后面将其定义改写为内联函数. 因此上述代码与直接在类中声明定义函数是一样的.

每一个新对象都有自己的存储空间用于存储器内部变量与类成员, 但同一个类的所有对象共享同一组类方法.

### 构造函数与析构函数

类对象不能使用列表初始化, 因为一些数据成员是私有的. 需要创建合适的成员函数: 构造函数, 在创建对象时被调用. 与类名称相同, 没有返回值. 

构造函数的参数列表中参数名不能与类成员相同.

C++ 提供两种调用构造函数方法:

```cpp
//显式
Stock food = Stock("World Cabbage", 250, 1.25);
//隐式
Stack food("World Cabbage", 250, 1.25);
```

每次创建类对象时, C++都使用类构造函数. 即使使用对象指针:

```cpp
Stock * pstock = new Stock("World Cabbage", 250, 1.25);
```

无法使用对象调用构造函数, 因为构造函数是用来创造对象的, 不能被对象调用.

**默认构造函数**

未提供显式初始值时用来创建对象的函数. 他将创建对象, 但不进行初始化. **当且仅当没有定义任何构造函数时, compiler才会提供默认构造函数. 一旦定义了构造函数, 那么就必须为它提供默认构造函数.**可以使用默认值的方式或重载构造函数.

```cpp
Stock first("Call constructor")
Stock second(); // this is a function whose return-type is Stock
Stock third; // Call the default-constructor
```

****

**析构函数**:对象过期时, 程序将自动调用析构函数, 清理内存空间. `~Stock(){...}`

调用析构函数的时机由compiler决定. 

**可以使用列表初始化对象, 只要提供与某个构造函数参数列表相匹配的内容即可.**

const 成员函数

```cpp
const Stock land = Stock("KKKKK");
land.show() //ERROE!!! show()can not guarantee don't modify variables
```

可以将函数参数设置为const解决? 但... show()没有参数列表...

将const关键字放在函数括号后:`void show() const;`

将类函数声明为const函数.

*当构造函数只有一个参数时允许`Bozo tubby = 20;`这样的初始化,  但其可能带来不愉快的意外.*

## this指针

成员函数有时需要处理两个对象, 这时需要用到this指针.

例如这样一个场景: 比较两个对象的某成员变量的大小.

必须将一个对象作为参数传进去, 这样会隐式访问自身的变量, 显式访问另一个对象的变量. 为了效率考虑, 传引用, 返回引用.

```CPP
const Stock& topval(const Stock& s) const;
```

上述的三个`const`: 括号内的const代表函数不会修改显式传入的对象; 最后的const代表函数不会修改隐式访问的对象; 因为函数返回两个const对象之一, 因此返回类型也是const引用.

如何实现呢?

```cpp
const Stock& topval(const Stock& s) const
{
  if (s.total_val > total_val)
    return s;
  else
    return ???;
}
```

如何称呼调用该方法的对象? 使用this指针.

this指针指向用于调用成员函数的对象.

`return *this;`

*每个成员函数都有一个this指针, 指针指向调用对象. 如果要引用整个调用对象, `*this`*

## 对象数组

`Stock mylist[4];`与声明数组的方式类似.

可以使用构造函数初始化, 每个元素都调用构造函数:

```cpp
Stock mylist[4]= {
  Stock("1",2,3),
  Stock(),
  Stock("3")
};
```

剩下的一个元素使用默认构造函数.

因此总结初始化对象数组的方式: **首先使用默认构造函数创建数组元素, 然后使用列表初始化构造临时对象, 将其内容复制到对应元素中. 因此, 要创建对象数组, 必须有默认构造函数.**

## 类作用域

类中定义的名称的作用域为整个类, 在类外是不可知的. 不能从外部直接访问类成员, 必须通过对象.

**作用域为类的常量**

如何创建一个所有对象共享的常量?

```cpp
class Bakey{
  private:
  const in months = 12;
  double costs[months];
  ...
};
```

这样是行不通的, 因为声明类只是描述了对象的形式, 并没有创建对象. 因此在创建对象前, 没有分配内存空间. 

可以使用如下方式:

```cpp
class Bakey{
  private:
  enum{months = 12};
  double costs[months];
  ...
};
```

枚举并不会创建数据成员, 所有对象中都不会包含枚举, 只是一个符号名称, 编译器会用12来替换他.

或使用`static`

```cpp
class Bakey{
  private:
  static const in months = 12;
  double costs[months];
  ...
};
```

这将创建一个months的常量, 该常量与其他静态常量存储在一起, 而不是在对象中. 因此只有一个months常量被所有Bakey对象共享.

****

作用域内枚举

传统枚举可能会出现冲突:

```cpp
enum egg{one, two, three, xx};
enum meat{one, two, three, ss};
```

C++11提供新枚举, 其枚举的作用域为类

```cpp
enum class egg{one, two, three, xx};
enum class meat{one, two, three, ss};// struct also okay
```

可以使用枚举名来限定枚举量

```cpp
egg choice = egg:: one;
meat buy   = meat::two;
```

但作用域内枚举不可隐式转换为整型.可显式转换.

可显式指定类型:

```cpp
enum class: short pizza{small, medium, large};
```

