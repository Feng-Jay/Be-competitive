# Lec2's notes and exercises'solutions

## Shell Script

之前对于shell的认识仅仅停留在shell的命令很多很复杂，还编写shell脚本。因此本节课的很多东西对我来说都比较新颖，所以笔记可能有些naive...

### ' 与 "

首先是在上节课的exercise中提到的`'`和`"`的区别问题，前者仅会保留字符的表面含义，后者则会进行部分expansion。

### Bash function

一个简单的例子:

```bash
mcd () {
    mkdir -p "$1"
    cd "$1"
}
```
其中的 `$`定义的含义如下：

- `$0`： 脚本名称
- `$1`~`$9`: 脚本传入参数, `$1`为第一个参数，以此类推。
- `$@`: 所有参数
- `$#`: 参数数目
- `$?`: 前一条命令的返回值
- `$$`: 执行当前脚本的进程PID
- `!!`: 上一条命令(包括参数), 一般由于权限问题时可使用 `sudo !!`快速键入
- `$_`: 上一条命令的最后一个参数。

`shell`中的条件判断与C类似。但逻辑似乎相反，`true`返回`0`, `false`返回`1`
同一行的命令也可以通过`;`进行分隔。

*****

**如何将命令输出进行存储**

将输出存入变量中，可以使用 `$(CMD)`的形式，它会执行`CMD`然后将执行结果替换在相应的位置。

```bash
foo=$(pwd)
echo "foo"
*output: /root/Be-competitive/examples*
```

将命令输出存为临时文件, 可以使用 `<(CMD)`, 会执行`CMD`并将输出存入一个临时文件。

```bash
cat <(ls) <(ls ..)
*output: 
mcd.sh
test.txt
examples
Missing-Semester
README.md*
```

### 匹配与脚本运行

`shell`中也有着通配符，分别为`?`与`*`，前者可以匹配1个任意字符，后者可以代表任意长度的任意字符。*与c类似*

`shell`中的`{}`可以用来扩展命令,example:

```bash
convert image.{png,jpg}
# Will expand to
convert image.png image.jpg

cp /path/to/project/{foo,bar,baz}.sh /newpath
# Will expand to
cp /path/to/project/foo.sh /path/to/project/bar.sh /path/to/project/baz.sh /newpath

# Globbing techniques can also be combined
mv *{.py,.sh} folder
# Will move all *.py and *.sh files


mkdir foo bar
# This creates files foo/a, foo/b, ... foo/h, bar/a, bar/b, ... bar/h
touch {foo,bar}/{a..h}
touch foo/x bar/y
# Show differences between files in foo and bar
diff <(ls foo) <(ls bar)
# Outputs
# < x
# ---
# > y
```

**也可以使用其他语言的script，只需要在shebang里给出对应编译器的路径**

### Shell Function 和 Shell Script 的不同

1. `Function`必须和`shell`使用同一种语法，但`Script`可以使用不同的语言，例如前面提到的`Python`

2. `Function`加载一次后就不用再加载，但`Script`每次执行都要重新加载。

3. `Function`执行在当前的`shell`环境中，而`Script`由一个单独进程执行。这也导致前者可以改变一些环境变量，比如`PWD`; 但后者不可以直接实现，需要通过`export`关键字进行改变。

## Shell tools

### 如何使用一些命令

> 使用命令的 `-h` / `--help` 的flag

> 使用`man`程序, 会得到很多详细的信息

> 使用`TLDR`程序，可以得到很多例子

### 找到文件

使用`find`命令

some examples:

```bash
# Find all directories named src
find . -name src -type d
# Find all python files that have a folder named test in their path
find . -path '*/test/*.py' -type f
# Find all files modified in the last day
find . -mtime -1
# Find all zip files with size in range 500k to 10M
find . -size +500k -size -10M -name '*.tar.gz'
```

What's more, find也可以在找到文件后对其进行相应的操作

```bash
# Delete all files with .tmp extension
find . -name '*.tmp' -exec rm {} \;
# Find all PNG files and convert them to JPG
find . -name '*.png' -exec convert {} {}.jpg \;
```

`fd`命令也是对`find`的一个改良版本。

你也可以利用`locate`命令去更高效地找到特定名称的文件，他借用了`OS`对file system构建的数据库。但和传统数据库一样，存在着效率和更新问题，可以手动`updatedb`来更新。在大多数OS中, `updatedb`通过`cron`每天执行.

### 找到文件内容

使用`grep`命令

也有很多类似改进的命令: `rg/ack/ag`

### 找到shell命令

> 可以使用`history`命令列出之前的历史命令. 使用`history | grep xxx`进行筛选。

> 使用 `Ctrl + R`查找历史命令，按着他就可以浏览fuzzing过的结果

### 快速切换目录

`fasd`和`autojump`命令可以根据频率和近似度跳转到预期的目录

`tree`和`broot`可以给出目录树

## Exercises






