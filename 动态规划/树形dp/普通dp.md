# 普通dp问题

## CFR 525 div2 E.

### 题意

给定一棵树，树上每个结点都有权值（正负），你可以选定k个连通块，使得这k个连通块的权值和的平均值最大。当有多种方案可以使得平均值最大时，选择k更大的方案，输出平均值和k。 要求复杂度O(n)。

### 题解

贪心来看，显然只选一块答案是最优的，因为max总是大于average。所以我们可以先通过选一块的策略来使得平均值最大，这个dp非常好写

dp[x] = val[x] + sum(dp[to] > 0 ? dp[to] : 0)

接下来就是找有多少个块是满足要求的（使得k最大），这个可以从下往上做，每形成一个可行的块就删掉，也是贪心的做法，这样做就可以使得块数是最大的。（因为高度再减小是没有意义的）

[代码](https://github.com/DSaurus/ACM_note/blob/master/data/cfr_525_e.cpp)