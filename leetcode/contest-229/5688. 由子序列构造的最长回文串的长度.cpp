#include <bits/stdc++.h>
using namespace std;
/*
很容易想到可以先把 `w2` 翻转一下，然后用公共子序列求出长度 `t`，两个组合就一定是一个长为 `2*t` 回文串，但是注意还需要加上 `w1` 或者 `w2` 自身的回文子序列来构成一个更长的回文串

例子 1：

- `w1` = `cacb`, `w2` = `cbba`；记 `w2` 反转之后为 `w2'` = `abbc`

    答案就是 `[ab][c][ba]`，其中第 1 部分和第 3 部分是 `w1` 和 `w2'` 的最长公共子序列，第 2 部分为 `w2` 自己的长为 1 的回文序列

- `w1` = `abaxyzcbc`, `w2` = `mnmzyx`；记 `w2` 反转之后为 `w2'` = `xyzmnm`

    答案就是 `[xyz][cbc][zyx]`，其中第 1 部分和第 3 部分是 `w1` 和 `w2'` 的最长公共子序列，第 2 部分为 `w1` 自己的长为 3 的回文子序列

    注意答案也可以是 `[xyz][mnm][zyx]`，但是不能是 `[xyz][cbc][mnm][zyx]`，也就是说 `w1` 和 `w2` 只能两者选一个，选择自身的回文子序列来拼接，我们选最长的那个即可

所以这个题实际上是「[AcWing 897. 最长公共子序列](https://www.acwing.com/problem/content/899/)」和「[LeetCode 516. 最长回文子序列](https://leetcode-cn.com/problems/longest-palindromic-subsequence/solution/dong-tai-gui-hua-si-yao-su-by-a380922457-3/)」的结合版

定义集合属性（下标均从 1 开始，方便 dp 的状态转移）：
- `f1[i][j]` 表示 `w1[i~j]` 内的最大回文子序列长度
- `f2[i][j]` 表示 `w2'[i~j]` 内的最大回文子序列长度
- `f[i][j]` 表示 `w1[1~i]` 和 `w2'[1~j]` 的最长公共子序列

上面 3 个数组的计算方式可以参考上面两个模板题。

最终的结果为

```
max_{i, j} {
    2 * f[i][j] + max(f1[i+1][n], f2[j+1][m])
}
```

其中 `n` 和 `m` 分别为 `w1` 和 `w2'` 的长度
*/

const int N = 1e3 + 10;
int f[N][N], f1[N][N], f2[N][N];
class Solution {
    void calSub(string& w1, int n, int f1[][N]) {
        // 最长回文子序列，区间 dp 模板
        for (int len = 1; len <= n; len++) {
            for (int i = 1; i + len - 1 <= n; i++) {
                int j = i + len - 1;
                if (len == 1)
                    f1[i][j] = 1;
                else {
                    f1[i][j] = max(f1[i + 1][j], f1[i][j - 1]);
                    if (w1[i] == w1[j]) {
                        f1[i][j] = max(f1[i][j], f1[i + 1][j - 1] + 2);
                    }
                }
            }
        }
    }

   public:
    int longestPalindrome(string w1, string w2) {
        int n = w1.length(), m = w2.length();
        // 翻转得到 w2'
        reverse(w2.begin(), w2.end());
        int ans = 0;
        memset(f, 0, sizeof f);
        memset(f1, 0, sizeof f1);
        memset(f2, 0, sizeof f2);
        // 加上空格，这样字符串从 1 开始索引，避免处理边界
        w1 = ' ' + w1, w2 = ' ' + w2;

        calSub(w1, n, f1);
        calSub(w2, m, f2);

        // 最长公共子序列模板
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                f[i][j] = max(f[i][j - 1], f[i - 1][j]);
                if (w1[i] == w2[j])
                    f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);

                // w1 和 w2 选的子序列要非空，等价于公共子序列非空
                if (f[i][j]) {
                    ans = max(ans, 2 * f[i][j] + max(f1[i + 1][n], f2[j + 1][m]));
                }
            }
        }

        return ans;
    }
};
