# Lecture3's note and exercises' solutions Lecture Lecture3's 

# vim 基础

由于之前接触过vim， 所以在这里主要记录一些对我而言有技巧的操作

> `O`/`o` 在之上/之下插入行

> `d{motion}`: delete{motion}
>> 例如 `dw` 删除一个word, `d$` 删除至行尾, `d0` 删除至行首

> `c{motion}`: change{motion}/等价于 d{motion} + i
>> `cw`: change word

> `x` delete character (equal do dl)

> `s` substitute character (equal to xi)

> 可以将数字与前面的内容结合
>> `3w` 前进3个words  
`5j` 向下移动5行
`7wd` 删除7个单词

> `ci(`: change 当前()内的内容
> 
> `ci[`: change 当前[]内的内容
> 
> `da' `: delete '' 包裹内容及''

接下来我安装了推荐的多个插件，并开始真正使用`vim`.


