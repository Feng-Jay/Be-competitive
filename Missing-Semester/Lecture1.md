# Lecture one's note and solutions to exercises

## Notes

课上提到了很多命令的使用和权限问题。在此不一一赘述，令我印象较深的是关于 `权限与连接`的问题和目录文件的执行权限的概念。

对于一个`directory`即目录文件的执行权限是很重要的。我们进入一个目录文件其实就需要拥有`x`执行权限。

例如：

```shell
sudo echo 3 > brightness
```
程序此时并不会正常执行，反而会报错 

>An error occurred while redirecting file 'brightness'open: Permission denied

这是因为重定向符是由shell来管理完成的，`echo` 程序并不知道自己在向`brightness`文件中写数据，这和Linux中的文件描述符的概念有些相像。

所以此时`echo`程序是以super user的权限执行的，但对`brightness`文件的写仍是以普通用户的权限进行的，导致ERROR。

## Solutions to Exercises

>1.Create a new directory called missing under /tmp.
