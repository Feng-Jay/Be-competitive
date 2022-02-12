# Lecture5's notes and solutons

## Job Control

学习通过shell对进程管理

进程间通过信息交流机制来控制进行，例如

`Ctrl-c`让shell对进程传递`SIGINT`信号 

`Ctrl-\`让shell对进程传递`SIGQUIT`信号

`Ctrl-Z`让shell对进程传递`SIGSTOP`信号

也可以使用`kill`指令向指定进程传递信号，默认为`SIGTERM`信号

***
可以通过 `fg`/`bg`让暂停的进程恢复前台或者后台运行。

后台进程仍然是你终端的子进程，如果退出终端会向其发送`SIGHUP`信号，可使用 `nohup`启动进程/`disown`更改正在运行的进程来避免这种情况。

`SIGKILL`信号无法被进程捕获，总是会立即结束进程。


## Tmux 

好用的终端分屏工具

>Sessions - a session is an independent workspace with one or more windows.  
>> `tmux` starts a new session.  
>> `tmux new -s NAME` starts it with that name.  
>> `tmux ls` lists the current sessions  
>> Within tmux typing `<C-b> d` detaches the current session  
>> `tmux a` attaches the last session. You can use `-t` flag to specify which  

> Windows - Equivalent to tabs in editors or browsers, they are visually separate parts of the same session.  
>>`<C-b> c` Creates a new window. To close it you can just terminate the shells doing `<C-d>`  
>> `<C-b> N` Go to the N th window. Note they are numbered  
>> `<C-b> p` Goes to the previous window  
>> `<C-b> n` Goes to the next window  
>> `<C-b> ,` Rename the current window  
>> `<C-b> w` List current windows  

>Panes - Like vim splits, panes let you have multiple shells in the same visual display.   
>> `<C-b> "` Split the current pane horizontally    
>> `<C-b> %` Split the current pane vertically  
>> `<C-b> <direction>` Move to the pane in the specified direction. Direction here means arrow keys.  
>> `<C-b> z` Toggle zoom for the current pane  
>> `<C-b>` [ Start scrollback. You can then press `<space>` to start a selection and `<enter>` to copy that selection.  
>> `<C-b> <space>` Cycle through pane arrangements.

## Aliases

可以将一些常用/易错的命令取别名，方便使用

```zsh
alias alias_name="command_to_alias arg1 arg2"
```

注意`=`两边不能有空格

## Dotfiles

大多工具的设置文件都存放于以`.`开头的文件里面，网络上也有很多他人的dotfiles,我们可以借鉴或者上传自己的dotfiles以方便在各个机器上面迁移。

## SSH

我们越来越倾向于使用远程服务器来运行代码，常用ssh来进行连接。

很common的一个例子就是:

```shell
ssh foo@bar.mit.edu
or
ssh foo@192.168.0.1
```

也经常使用远程机器来执行命令

```shell
ssh foobar@server ls | grep PATTERN
```
会在本地对远程的ls输出进行PATTERN

```shell
ls | ssh foobar@server grep PATTERN
```
将会在远程对本地ls输出进行PATTERN

ssh 连接中最常用的一个概念就是`key`，[这是一篇关于SSH原理的讲解文章](https://segmentfault.com/a/1190000037563769)

[这是一篇关于port forwarding的文章](https://unix.stackexchange.com/questions/115897/whats-ssh-port-forwarding-and-whats-the-difference-between-ssh-local-and-remot)

# Exercises

## Job Control

1. 
```shell
❯ sleep 10000
^Z
[1]  + 16826 suspended  sleep 10000
❯ bg
[1]  + 16826 continued  sleep 10000
❯ pgrep "sleep"
16826
❯ pkill -f "sleep"
[1]  + 16826 terminated  sleep 10000
```

2. 见目录下`pidwait.sh`文件

## Terminal multiplexer

跟着完成教学即可

## Aliases

1. `alias dc="cd"`
2. 根据提示自己完成即可

## Dotfiles 
未看到自己的使用需求，未完成

## Remote machine 

已经操作过多个服务器/远程主机，比较熟练，skip。





