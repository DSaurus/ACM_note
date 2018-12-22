# 思维题

这里是思维题板块

## Avito Cool Challenge 2018 F题

### 题意

交互，给一个01串，每次询问一个区间[l,r]，随机[1,r]和[l,n]翻转并且返回翻转后1的个数，需要猜出01串。

### 题解

令[1,r]和[l,n]奇偶性不同，每次询问期望在7次内得到该位的结果并还原01串，串长为奇数时第一位需特殊处理。

[code](https://github.com/DSaurus/ACM_note/blob/master/data/acc2018_f.cpp)