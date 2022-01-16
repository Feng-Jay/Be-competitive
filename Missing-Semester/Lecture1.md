# Lec1's notes and exercises' solutions

## Notes

课上提到了很多命令的使用和权限问题。在此不一一赘述，令我印象较深的是关于 `权限与连接`的问题和目录文件的执行权限的概念。

例如：

```bash
sudo echo 3 > brightness
```
程序此时并不会正常执行，反而会报错 

>An error occurred while redirecting file 'brightness'open: Permission denied

这是因为重定向符是由shell来管理完成的，`echo` 程序并不知道自己在向`brightness`文件中写数据，这和Linux中的文件描述符的概念有些相像。

所以此时`echo`程序是以super user的权限执行的，但对`brightness`文件的写仍是以普通用户的权限进行的，导致ERROR。

其次就是对于一个`directory`即目录文件的执行权限是很重要的。我们进入一个目录文件其实就需要拥有`x`执行权限。

## Solutions to Exercises

>1.Create a new directory called missing under /tmp.

```bash
cd /tmp
mkdir missing
```

>2.Look up the touch program. The man program is your friend.

我们可以使用如下命令查看`touch`的man手册

```bash
man touch
```
>3.Use touch to create a new file called semester in missing.

```bash
touch /tmp/missing/semester
```

>4.Write the following into that file, one line at a time: 
>>```bash
>>#!/bin/sh
>>curl --head --silent https://missing.csail.mit.edu
>>```

这里的主要问题出现在第一行，如何处理`!`字符，通过查看网站给出的[手册](https://www.gnu.org/software/bash/manual/html_node/Single-Quotes.html)，可以了解到由`''`括起来的字符串的所有字符都会被解释为普通的字符含义, 即使用:
```bash
echo '#!/bin/sh' > semester
```

之前还想使用`""`括起来的字符串，通过一个`\`将`!`转义一下，但根据[手册](https://www.gnu.org/software/bash/manual/html_node/Double-Quotes.html)内容, 这样处理的`!`前的`\`并不会被消除，所以这个方法被PASS掉了。

对于第二行而言使用上述方法应该也很容易解决。课余时间阅读一下[Bash History](https://www.gnu.org/software/bash/manual/html_node/Bash-History-Facilities.html)的内容。

>5.Try to execute the file, i.e. type the path to the script (./semester) into your shell and press enter. Understand why it doesn’t work by consulting the output of ls (hint: look at the permission bits of the file).

通过按照题目执行文件，发现结果如下：

```bash
ffengjay@MitLab:/tmp/missing$ ./semester
bash: ./semester: 权限不够
```
通过`ls -l`命令发现权限如下:
```bash
-rw-rw-r-- 1 ffengjay ffengjay 61 12月 25 15:19 semester
```
发现是因为我们并没有执行权限导致无法直接运行脚本

>6.Run the command by explicitly starting the sh interpreter, and giving it the file semester as the first argument, i.e. sh semester. Why does this work, while ./semester didn’t?

通过执行 `sh semester`发现结果如下：
```bash
ffengjay@MitLab:/tmp/missing$ sh semester
HTTP/2 200 
server: GitHub.com
content-type: text/html; charset=utf-8
last-modified: Thu, 09 Dec 2021 04:11:14 GMT
access-control-allow-origin: *
etag: "61b181e2-1f31"
expires: Mon, 20 Dec 2021 10:45:19 GMT
cache-control: max-age=600
x-proxy-cache: MISS
x-github-request-id: 673E:0AB9:2F9AB5:3264A6:61C05C67
accept-ranges: bytes
date: Sat, 25 Dec 2021 07:21:18 GMT
via: 1.1 varnish
age: 0
x-served-by: cache-hnd18723-HND
x-cache: HIT
x-cache-hits: 1
x-timer: S1640416878.939350,VS0,VE149
vary: Accept-Encoding
x-fastly-request-id: 5615e48b91cf38f2b84b4579f5acceca28266cbe
content-length: 7985
```
通过[STFW](https://stackoverflow.com/questions/42712407/why-shell-script-wont-run-when-executed-directly-but-runs-with-usr-bin-sh-or)
可以得知对于sh脚本我们是拥有执行权限的:
```bash
lrwxrwxrwx 1 root root 4 9月  13 22:47 /usr/bin/sh -> dash
```
所以可以使用一个类似“借壳”的方式执行脚本

>7.Look up the chmod program (e.g. use man chmod).
通过如下命令可以得知chmod可用来改变文件权限
```bash
man chmod
```

>8.Use chmod to make it possible to run the command ./semester rather than having to type sh semester. How does your shell know that the file is supposed to be interpreted using sh? See this page on the shebang line for more information.

通过使用如下命令让我们拥有执行权限:
```bash
ffengjay@MitLab:/tmp/missing$ chmod 764 semester
```



>9.Use | and > to write the “last modified” date output by semester into a file called last-modified.txt in your home directory.

通过`man`手册查阅`grep`命令和`cut`命令对shell脚本执行结果进行处理，将结果重定向到指定TXT文件

```bash
ffengjay@MitLab:/tmp/missing$ ./semester | grep --ignore-case last-modified | cut -c 16-  > last-modified.txt
ffengjay@MitLab:/tmp/missing$ cat last-modified.txt 
Thu, 09 Dec 2021 04:11:14 GMT
```
`wikipedia`上的解释是:

>>When a text file with a shebang is used as if it is an executable in a Unix-like operating system, the program loader mechanism parses the rest of the file's initial line as an interpreter directive. The loader executes the specified interpreter program, passing to it as an argument using the path that was initially used when attempting to run the script, so that the program may use the file as input data.[8] For example, if a script is named with the path path/to/script, and it starts with the following line, #!/bin/sh, then the program loader is instructed to run the program /bin/sh, passing path/to/script as the first argument. In Linux, this behavior is the result of both kernel and user-space code.[9]

在 shell(Bash 是一种 shell) 中执行外部程序和脚本时，Linux 内核会启动一个新的进程，以便在新的进程中执行指定的程序或脚本。内核知道该如何为编译型的程序做这件事，但是对于脚本程序呢？当 shell 要求内核执行一个脚本文件时，内核是不知道该怎么办的！所以它回应一个 "not executable format file" 的错误消息。Shell 收到这样的消息后会做出类似下面的判断：这不是个编译型程序，那它肯定是一个 shell 脚本；接着就启动一个新的 /bin/sh 副本来这些该程序。

当系统中只有一个 shell(/bin/sh) 时这并没有什么问题。但是当前的系统中一般都存在多个 shell，比如 Bash、Dash等等。因此需要通过一种方式，告诉 Linux 内核应该以哪个 shell 来执行指定的脚本。实时上，这么做有助于执行机制的通用化，让用户可以直接引用任何的程序语言解释器，而不仅仅是一个 shell。具体的方法是通过脚本文件中特殊的第一行来设置：在第一行的开头处使用 #! 这两个字符(英文一般称为 shebang)。

当一个脚本中第一行是以 #! 这两个字符开头时，内核会扫描该行的其余部分，看是否可以找到可以用来执行该脚本文件的解释器。所以这是一种非常通用的做法，因为除了 shell 我们还可以指定其它的解释器，比如：

```bash
#!/usr/bin/awk
# 这个脚本是一个 awk 程序
```
[参考博客](https://www.cnblogs.com/sparkdev/p/9843024.html)

>10.Write a command that reads out your laptop battery’s power level or your desktop machine’s CPU temperature from /sys. Note: if you’re a macOS user, your OS doesn’t have sysfs, so you can skip this exercise.

由于我使用的是Ubuntu虚拟机，似乎好像找不到相应文件......但也不确定，如果大家有思路可以教我一下。
