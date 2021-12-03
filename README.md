# Prisoner-Dilemma
Realization of a Protocol Concerning Prisoner's Dilemma

## 重要提示
此项目使用 Visual Studio 2022 进行编译. Visual Studio 2019 项目生成时可能出现错误: 
    "代码MSB8020: 无法找到 v143 的生成工具"
建议更新 Visual Studio 版本, 或者将源代码复制到新建的 Visual Studio 2019 解决方案中编译运行. 

## 文件说明

代码中的protocol.h为需要的宏定义以及函数定义，PROTOTYPE.cpp为目前使用的原型决策程序，credit.cpp为计算信用分所使用的的源代码。
文件中.tex文件对应于协议的源码,.pdf文件对应于协议内容。具体介绍如下: 

// protocol.h //

i)   定义了决策程序中必要的参数;

ii)  定义了一个枚举类型 protocol_code, 用于计算各选手的信誉分, 同时也作为决策的参考;

iii) 声明了一个函数 credit 的原型, 其定义在 credit.cpp 中.



// credit.cpp //

定义了一个 "计算信誉分" 函数, 其主要功能是:

读取比赛双方选手的决策记录, 同时根据 protocol_code 的指示, 按照文件 ".\Prisoner's Dilemma\Protocol Documents\Pastoral Protocal 1.0.pdf" 的
规则实时计算双方的信誉分. 该信誉分将用于决策.



// MODEL.cpp //

最终的决策函数，当naive出现率较低时表现非常优秀。
