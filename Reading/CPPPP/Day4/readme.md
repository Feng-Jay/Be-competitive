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

