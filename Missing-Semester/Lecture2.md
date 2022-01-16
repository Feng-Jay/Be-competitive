# Lecture two's note and solutions to the exercise

## Note

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

## 匹配与脚本运行

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





