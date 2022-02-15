# Version Control(Git)

## Git‘s data model

在`git` 术语中:

```c
file 被称为 blob
directory 被称为 tree (maps names to blobs or trees)
顶层被追踪的tree 被称为 snapshot
    
//pseudocode
// a file is a bunch of bytes
type blob = array<byte>

// a directory contains named files and directories
type tree = map<string, tree | blob>

// a commit has parents, metadata, and the top-level tree
type commit = struct {
    parents: array<commit>
    author: string
    message: string
    snapshot: tree
}
```

例如：

```shell
<root> (tree)
|
+- foo (tree)
|  |
|  + bar.txt (blob, contents = "hello world")
|
+- baz.txt (blob, contents = "git is wonderful")
```

顶层树包括两个元素：`foo` tree 和 `baz.txt` blob



Git 使用 ==DAG==的格式组织snapshot:

> 这意味着每个snapshot都会有若干个父母结点
>
> Git将这些snapshots称为==commit==

``` c
//一些示例
o <-- o <-- o <-- o
            ^
             \
              --- o <-- o
OR

o <-- o <-- o <-- o <---- o
            ^            /
             \          v
              --- o <-- o
```

## Objects and content-addressing

```c
type object = blob | tree | commit
```

在git的数据存储中，所有的`object`(blob | tree | commit )均通过SHA-1 hash的方式通过内容寻址

虽然这种方式可以完成对数据的寻址，但对人类并不友好**每次都需要输入长串的hash值**，所以git提出了==references==的概念。

**References**是指向cmmmit的指针，与`object`不同，**References是可变的。**

* 例如`master`总是指向主分支上最近一次commit
* `HEAD`总是指向我们当前所在的位置

***

至此，我们可以给出==repository==的定义：

> Repository 是 objects 和 references的数据

在磁盘上，git保存的数据就是objects 和 references。这就是git 数据模型的全部内容。

**所有的git命令都是在DAG图上进行操作**：通过添加objects/添加修改references

## Staging area

在很多时候，我们并不想直接将项目的当前状态作为一个snapshot保存起来，例如你正在实现项目中的两个特性，你想要创建两个commit，分别介绍两个特性。

Git的缓存区可以让你决定**在下一个commit中哪些信息应该被保留。**

## Git command-line interface

1. **Basic**

   ```bash
   git help <command>
   git init : 创建一个新git repo 
   git status  : 查看当前的情况
   git add <filename> : 将file存入staging area
   git commit : 创建新的commit	
   git log : 显示普通的提交历史
   git log --all --graph --decorate : 通过DAG图可视化提交历史 
   git diff <filename> : 显示对于staging area文件所做的修改
   git diff <revision> <filename> : 显示不同snapshot间文件的不同
   git checkout <revision> : 更新HEAD/切换分支
   ```



2. Branch and merge

```shell
git branch : 显示分支
git branch <name> : 创建分支
git checkout -b <name> : 创建分支并切换到上面
git merge <revison> : 合并到当前分支
git mergetool : 解决合并冲突问题
git rebase : 将一系列补丁转移到新的基上
```



3. Remotes

   ```shell
   git remote : 列出远程仓库
   git remote add <name> <url> : 添加远程仓库
   git push <remote> <local branch>:<remote branch> : 
   将objects上传，更新remote
   
   git branch --set-upstream-to=<remote>/<remote branch> :
   建立本地和远程分支的对应关系
   
   git fetch : 从远程仓库拉取objects/references
   git pull : <==> git fetch + git merge
   git clone : 从远程下载仓库
   ```

   

4. Undo

   ```shell
   git commit --amend : 修改commit的内容/信息
   git reset HEAD <file> : 取消暂存文件
   git checkout -- <file> : 放弃更改
   ```

5. Advanced git 

   ```shell
   git config : 设置git
   git clone --depth=1 : 浅clone
   git add -p : 交互式缓存
   git rebase -i : 交互式rebase
   git blame : 显示谁最后改了某一行
   git stash : 暂时删除对于工作目录的修改
   git bisect : 二分查找历史
   .gitignore : 忽略文件
   ```

   ## Exercises

1. 完成了[Learn Git Branching](https://learngitbranching.js.org/?locale=zh_CN)的教学内容

2. Clone [repository for the class website](https://github.com/missing-semester/missing-semester)

   - ```shell
     git log --all --graph --decorate
     ```

   - ```shell
     git log README.md
     ```

   - ```shell
     git blame _config.yml | grep "collections:"
     得到
     13ae56f5 (Anish Athalye 2020-01-17 15:26:30 -0500 18) collections:
     git show 13ae56f5
     ```

3. ```shell
   git filter-branch --force --index-filter "git rm --cached --ignore-unmatch PATH" --prune-empty --tag-name-filter cat -- --all
   filter-branch 让git重写每一个分支，
   –force 假如遇到冲突也让git强制执行，
   –index-filter 选项指定重写的时候应该执行什么命令，要执行的命令紧跟在它的后面，在这里就是git rm --cached --ignore-unmatch password.txt ，让git删除掉缓存的文件，如果有匹配的话（具体删除哪种类型就按哪种命令来执行就可以）。
   –prune-empty 选项告诉git，如果因为重写导致某些commit变成了空(比如修改的文件全部被删除)，那么忽略掉这个commit。
   –tag-name-filter 表示对每一个tag如何重命名，重命名的命令紧跟在后面，当前的tag名会从标注输入送给后面的命令，用cat就表示保持tag名不变。
   紧跟着的-- 表示分割符，
   最后的–all 表示对所有的文件都考虑在内。
   ```

4. ```shell 
   git stash会将当前的修改暂时隐藏, 使用 git stash pop 后可恢复。这在当你需要保存工作现场切换其他分支时有用。 
   ```

5. ```shell
   [alias]
   	graph = log --all --graph --decorate --oneline
   	pom = push origin master
   ```

6. 7. 略过