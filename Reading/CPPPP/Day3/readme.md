# Loop and branch

表达式与语句

C++中任何值或者任何有效的值与运算符的组合都是表达式, 每个表达式都有值: `33+36 x = 20`当表达式的值改变了内存中数据值时，我们说他们有side-effect

只要加上分号, 所有的表达式都可以变成语句。但不一定有意义. 但这句话反过来就不一定成立: 声明语句、返回语句、for循环语句都不满足。

C的for循环: `for(expression; expression; expression) statement;` 即for的控制部分由三个expression构成。

但C++允许 `for(int i=0; exp;exp)`存在，`for(for-init-statement condition; expression) statement`。只有一个分号，因为for-init-statement被视作一条语句，有自己的分号。

**逗号表达式**

逗号表达式花絮: 确保计算第一个表达式，然后计算第二个表达式;  逗号表达式的值是第二部分的值。

处理输入

cin中存在一个函数，当cin出现在需要bool值的时候会根据最后一次读取是否成功将其设置为true or false. 所以可以用以下处理输入:

```cpp
while(cin){}
while(cin.get(ch)){}
cin.get(ch) : 赋给参数ch;返回istream变量; 到达EOF也返回istream变量
ch=cin.get(): 将函数返回值给ch; 返回int型字符编码; 到达EOF时返回EOF常量
```
