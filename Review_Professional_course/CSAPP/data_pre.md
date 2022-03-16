**这是一个用来记录读书和lab过程中遇到的知识点和问题的Notebook!**

# 第二章 信息的表示和度量

1. `char`是有符号还是无符号？

大多认为是有符号的，但c标准中不保证这一点
`arm-linux-gcc 规定 char 为 unsigned char; vc 编译器、x86上的 gcc 规定 char 为 signed char`.

标准中提供了char, signed char 和unsigned char三种类型

2. 大多intel机器为小端序。但目前大多处理器为双端序，由具体os来确定真正是大端还是小端

在网络数据流传输，阅读数据，进行强制类型转换(引用对象)时有影响。

3. 