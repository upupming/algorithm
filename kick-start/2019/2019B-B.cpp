#include <iostream>
#include <algorithm>
using namespace std;

int t, n, s[110], e[110], l[110], idx[110], dp[10010], ts;

// O(n!), TLE

/**
secs, energy, lose
s  e  l
20 10 1
5 30 5
100 30 1
5 80 60

贪心排序，之后再进行dp
s  e  l  Got                accTime             s/l
5 80 60  80                 0+5=5               1/12
5 30 5  30-5*5=5            5+5=10              1/1
100 30 1 30-10*1=20         10+100=110          100/1
20 10 1  0                  110+20=130          20/1
尽量选择 Got 最多的石头，但是又不能直接去动态比较，否则就又相当于 n! 时间复杂度了
如何在一开始就确定吃石头的顺序，写一个 cmp 比较函数？

错误想法：似乎是按照 e 从大到小，然后 e 相同时 l 从大到小，l 相同时 s 从小到大的顺序

考虑编号为 i, j 的石头，如果 i 在 j 之前，总消耗能量为 s[i]l[j]；反之为 s[j]l[i]。
所以如果 s[i]l[j] < s[j]l[i]，就把 i 放在 j 之前，Analysis 部分利用反证法进行了证明

dp[time][j] 表示已用去 time 时间之后 [j, n] 的选择情况得到的最大值，省去第二维
*/

int cmp(int i, int j) { return s[i] * l[j] < s[j] * l[i]; }

int solve() {
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx, idx + n, cmp);
    
    // ts: 最长吃石头时间
    for (int i = 0; i <= ts; i++) dp[i] = 0;

    for (int i = 0; i < n; i++) {
        int index = idx[i];
        // 注意循环是 --，因为有空间优化
        for (int j = ts; j >= s[index]; j--) {
            // 吃第 i 块石头，用去了 s[index] 时间
            int tmp1 = dp[j - s[index]] + max(0, e[index] - l[index] * (j - s[index]));
            // 不吃第 i 块石头，保持不变
            dp[j] = max(dp[j], tmp1);
            // cout << i << ", " << j << ", " << dp[j] << endl;
        }
    }
    int ans = 0;
    for (int i = 0; i <= ts; i++) ans = max(ans, dp[i]);

    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        ts = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &s[i], &e[i], &l[i]);
            ts += s[i];
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}