# Google KickStart 2021 Round C

- A 题 WA 了，难受，没心思做后面题导致全部拉跨，只 A 了 B 题
    - 写出正确的实现非常关键，不能再写 Bug 了

## A. Smaller Strings

- 类似数位 DP，枚举每一位的填法即可
- 边界情况需要格外注意，下面这个特殊例子，填 `baa` 之后，最后一位是可以填 `a` 的，因为 `reverse(baa)=aab < abd`，注意 `a`  相同所以延续到 `a<b` 来做比较，实际实现时通过 `ok` 的传递来实现

    ```txt
    7 5
    baaaabd
    ```
    - 比赛的时候想到了比较 `s[i]` 与 `s[n-1-i]`，但是没想到相同的时候需要延续到 `s[i-1]` 与 `s[n-i]`，构造很多测试用例也没构造到上面这个例子，所以就一直 WA

## B. Alien Generator

- 推公式可得: `k = (2g-i^2+i)/(2i)`，因此 `2g-i^2+i>0`，因此 i 的范围是 `[1-sqrt(1-8g)]/2` 到 `[1+sqrt(1-8g)]/2`，这个范围是 `sqrt(g)` 大小的，直接暴力枚举所有 `i` 判断求出的 `k` 是不是整数即可。

## C. Rock Paper Scissors

- 暂时没有思路

## Binary Operator

- 想到的是类似字符串哈希的算法，随机生成一些函数，通过多次随机检测，如果结果都相同，则认为是一类
- 需要写高精度，所以比赛时还是优先转向 A 题，结果 A 题爆炸。。。