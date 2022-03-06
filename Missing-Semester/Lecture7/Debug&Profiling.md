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









