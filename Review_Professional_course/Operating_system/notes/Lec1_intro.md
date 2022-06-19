# Why is Operating System

充满热情而且相当聪明的学生...早就听说过物理学如何有趣...相对论、量子力学……但是，当他们学完两年以前那种课程后，许多人就泄气了……学的还是斜面、静电这样的内容 ——Feynman

# What is Operating System

Operating System: A body of software, in fact, that is responsible for *making it easy to run programs* (even allowing you to seemingly run many at the same time), allowing programs to share memory, enabling programs to interact with devices, and other fun stuff like that. (OSTEP)

**1940s**:ENIAC, 逻辑门：真空电子管；存储器：延迟线；输入输出：打孔纸带。并没有OS

**1950s**：IO速度严重低于cpu速度，中断机制出现，Fortran诞生。开始有了OS概念

**1960s:** 更快的处理器，更大的内存/虚拟存储器，更丰富的IO。能载入多个程序到内存且灵活调度它们的管理程序，包括程序可以调用的 API。也出现了分时系统

**1970s:** 计算机与今日无太大差异。分时系统走向成熟，UNIX 诞生并走向完善，奠定了现代操作系统的形态。

**今天的OS**:通过 “虚拟化” 硬件资源为程序运行提供服务的软件。非对称CPU，NUMA，更多的硬件机制与设备

## OS的三个根本问题

服务谁？程序（状态机）

为程序提供什么服务？对象+API

如何实现OS提供的服务？操作系统=c程序，初始化后就成为interrupt/trap/fault handler

# How to learn Operating System

**Get Your Hands Dirty**