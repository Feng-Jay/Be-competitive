**Code does not do what you expect it to do, but what you tell it to do.**

# Debugging

我们最常使用的就是 `printf` 式的debug方法，但这种方法需要随着程序迭代也进行升级。可以选择更好的`logging`的方式，其优点有：

* 可以log向`files/socket/server`, 而非仅仅是标准输出

* log方法支持对问题严重程度进行分级：INFO, DEBUG, WARN, ERROR...

* 对于新的问题，log也可以给出足够的信息

在MACOS中可以通过 `echo -e "\e[31;1mThis is red\e[0m"`的方式给输出附上颜色。采用了ANSI escape code。

很多程序都会向os中写入他们的log记录，macos中有`/var/log/system.log`, 可以使用`log show`命令对查询内容进行定义。也可以使用`logger`命令向系统log记中写入内容：

```zsh
logger "Hello Logs"
# On macOS
log show --last 1m | grep Hello
```

不管是printf还是logging的debug方式都无法控制程序运行的过程。如果我们想要逐步调试程序或者获得程序执行中的某些信息，我们可以使用**debugger**。

对于python来说，我们可以使用pdb/ipdb来进行debug:

> 1. l(ist) Displays 11 lines around the current line or continue the previous listing.

2. s(tep) - Execute the current line, stop at the first possible occasion.

3. n(ext) - Continue execution until the next line in the current function is reached or it returns.

4. b(reak) - Set a breakpoint (depending on the argument provided).

5. p(rint) - Evaluate the expression in the current context and print its value. There’s also pp to display using pprint instead.

6. r(eturn) - Continue execution until the current function returns.

7. q(uit) - Quit the debugger.

对于更低层次的编程或者使用类c语言，可以使用gdb来进行debug。

当你面临的程序处于黑箱状态: 即无法看到内部实现时，你也可以通过一些工具来debug。
当程序需要执行只有内核才能实现的操作时会调用`system call`. Macos 上可使用dtruss命令进行查看

```shell
# On macOS
sudo dtruss -t lstat64_extended ls -l > /dev/null
```
你可能会遇到`SIP`问题，这是一个[解决方案](https://stackoverflow.com/questions/60908765/mac-osx-using-dtruss)。

更多的情况下，我们并不需要运行代码，仅仅通过阅读代码就可以发现其中隐藏额的bug。有很多对应的`静态分析`工具来帮助我们。

* python中有 `pyflakes`和`mypy`.

* shell 中有 `shellcheck`

* 现代IDE中也集成了一些功能

* [Awesome Static Analysis](https://github.com/analysis-tools-dev/static-analysis)

* [Awesome Linters](https://github.com/caramelomartins/awesome-linters)

* Code formatter可作为上述Linter的辅助工具: black for Python, gofmt for Go, rustfmt for Rust...

# Profiling

即使我们的程序按照计划成功运行起来，但我们还需要对其进行优化。在优化前，必须对其现状有准确的评估，[premature optimization is the root of all evil](https://wiki.c2.com/?PrematureOptimization), 我们应该使用一些量化检测工具来帮助我们分析程序使用内存/时间的关键节点。

## Timing

程序运行的时间可以分为三部分:
1. Real time. 从程序开始到结束所花费的全部时间。包括其他进程运行的时间和程序阻塞的时间。

2. User time. 在CPU上运行用户代码的时间。

3. Sys time. 在CPU上运行内核代码的时间。

可以使用`time`命令，他会列出上述三种时间各自的值。

## Profiler

人们通常提到的Profiler都是指CPU, 分为两种: tracing and sampling profilers。简单来说就是一个是一直追踪(开销大)，另一种是周期性地检测。都可以给出程序中最耗时的动作。

Python中可以使用 `cProfile`:

```shell
python -m cProfile -s tottime grep.py 1000 '^(import|\s*def)[^,]*$' *.py
```

但它有一个问题，就是会给出每一个函数call花费的时间，导致给出的结果很多，不易查看。可以使用`line_profiler`来得到程序每一行花费时间。

```shell
kernprof -l -v a.py
```

同时，在C/C++中的内存泄漏可能导致程序无法释放不需要的内存。可以使用`valgrind`工具检测。

在有gc机制的语言——例如python中对于内存检测也是必要的，因为只要对象被指针指就不会被回收。可以使用`memory-profiler`来进行内存监测：

```python
@profile
def my_func():
    a = [1] * (10 ** 6)
    b = [2] * (2 * 10 ** 7)
    del b
    return a

if __name__ == '__main__':
    my_func()
```

```shell
$ python -m memory_profiler example.py
```
这也是一个逐行的检测器。

可以通过`flame graph`或者`call graph`来进行可视化。

**资源监测**

- General Monitoring. 使用`htop, glances, dstat`

- I/O operation. `iotop`显示io使用量

- Disk usage. `df, du`

- Meomory usage. `free`展示内存使用量

- Open files. `lsof`显示被进程打开的所有文件的信息。

- Network Usage. `nethogs, iftop`可用于监测。



# Exercises

## Debugging

1. 

```shell
log show --last 24h | grep "sudo*"
```

2. 

见项目中的pdb-tutorial目录

3. 

修改后的code:

```shell
#!/bin/sh
## Example: a typical script with several problems
for f in ./*.m3u
do
  grep -qi "hq.*mp3" "$f" \
    && echo "Playlist $f contains a HQ file in mp3 format"
done
```
然后在sublime中安装了shellcheck的插件

## Profiling

5. 

使用`cproflie`查看不同算法用时：

```shell
python3 -m cProfile -s time sorts.py
         590547 function calls (525858 primitive calls) in 0.125 seconds

   Ordered by: internal time

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
    78646    0.021    0.000    0.042    0.000 random.py:200(randrange)
     1000    0.018    0.000    0.018    0.000 sorts.py:11(insertionsort)
33646/1000    0.016    0.000    0.025    0.000 sorts.py:23(quicksort)
33016/1000    0.016    0.000    0.016    0.000 sorts.py:32(quicksort_inplace)
```

发现插入排序速度快于快速排序。然后通过`memory_profiler`对内存使用进行分析:

```shell
Line #    Mem usage    Increment  Occurrences   Line Contents
=============================================================
    10   41.688 MiB   41.625 MiB        1000   @profile
    11                                         def insertionsort(array):
    12                                         
    13   41.688 MiB    0.000 MiB       26825       for i in range(len(array)):
    14   41.688 MiB    0.000 MiB       25825           j = i-1
    15   41.688 MiB    0.000 MiB       25825           v = array[i]
    16   41.688 MiB    0.000 MiB      238520           while j >= 0 and v < array[j]:
    17   41.688 MiB    0.031 MiB      212695               array[j+1] = array[j]
    18   41.688 MiB    0.031 MiB      212695               j -= 1
    19   41.688 MiB    0.000 MiB       25825           array[j+1] = v
    20   41.688 MiB    0.000 MiB        1000       return array


Line #    Mem usage    Increment  Occurrences   Line Contents
=============================================================
    22   42.156 MiB   42.094 MiB       33958   @profile
    23                                         def quicksort(array):
    24   42.156 MiB    0.000 MiB       33958       if len(array) <= 1:
    25   42.156 MiB    0.031 MiB       17479           return array
    26   42.156 MiB    0.000 MiB       16479       pivot = array[0]
    27   42.156 MiB    0.000 MiB      158738       left = [i for i in array[1:] if i < pivot]
    28   42.156 MiB    0.031 MiB      158738       right = [i for i in array[1:] if i >= pivot]
    29   42.156 MiB    0.000 MiB       16479       return quicksort(left) + [pivot] + quicksort(right)

Line #    Mem usage    Increment  Occurrences   Line Contents
=============================================================
    31   41.531 MiB   41.438 MiB       34096   @profile
    32                                         def quicksort_inplace(array, low=0, high=None):
    33   41.531 MiB    0.000 MiB       34096       if len(array) <= 1:
    34   41.531 MiB    0.000 MiB          37           return array
    35   41.531 MiB    0.000 MiB       34059       if high is None:
    36   41.531 MiB    0.000 MiB         963           high = len(array)-1
    37   41.531 MiB    0.000 MiB       34059       if low >= high:
    38   41.531 MiB    0.000 MiB       17511           return array
    39                                         
    40   41.531 MiB    0.000 MiB       16548       pivot = array[high]
    41   41.531 MiB    0.000 MiB       16548       j = low-1
    42   41.531 MiB    0.062 MiB      126066       for i in range(low, high):
    43   41.531 MiB    0.031 MiB      109518           if array[i] <= pivot:
    44   41.531 MiB    0.000 MiB       57470               j += 1
    45   41.531 MiB    0.000 MiB       57470               array[i], array[j] = array[j], array[i]
    46   41.531 MiB    0.000 MiB       16548       array[high], array[j+1] = array[j+1], array[high]
    47   41.531 MiB    0.000 MiB       16548       quicksort_inplace(array, low, j)
    48   41.531 MiB    0.000 MiB       16548       quicksort_inplace(array, j+2, high)
    49   41.531 MiB    0.000 MiB       16548       return array
```

发现普通的快速排序需要的内存空间 > 插入排序的 > 原地交换的快速排序。可以得知插入排序可以原地交换数据，所以内存表现优于快速排序。

6. 

fib0被调用了21次。

使用注释内容后fibN只被调用1次

7. 

使用上述命令后出现
```shell
Python 10300 *** *** ***... *** TCP *: krb524 (LISTEN)
```
然后使用

```shell
kill 10300
<另一边>
python -m http.server 4444
Serving HTTP on :: port 4444 (http: //[::]:4444/)
[1] 10300 terminated /usr/bin/python3 -m http.server 4444
```

8.

并没有占用3个cpu，因为taskset限制了使用的资源。





