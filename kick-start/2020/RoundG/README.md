# KickStart Round G 题解

## A. Kick_Start

### 算法 - 暴力枚举

- 遍历一遍字符串，累计当前有多少 `KICK`，记为 `k`
- 遇到一个 `START`，一定能够和前面的 `k` 个 `KICK` 都构成 `KICK*START`，因此答案累加上 `k`

### 时间复杂度

- 线性扫描：O(n)

### C++ 代码

```cpp
#include <iostream>
using namespace std;

int t;
string s;

int solve() {
    int n = s.length();
    int k = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        if (s.substr(i, 4) == "KICK") k++;
        if (s.substr(i, 5) == "START") ans += k;
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> s;
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
```

## B. Maximum_Coins

### 算法 - 暴力枚举斜边

- 枚举所有斜边，每个斜边对应一个行 `i` 和列 `j` 的差 `d`
  - 有点类似区间 dp 的枚举方式，最外层循环都是用的 `i` 和 `j` 的差
- 统计斜边上所有的数的和 `sum`，如果大于当前答案，则更新答案
- 这题因为都是正数，所以肯定是对角线所有元素之和。如果可能有负数的话，就需要用 Kadane's algorithm, 参考蓝书 P30
- `N * C = 10^3 * 10^7` 会爆 `int`，需要用 `long long`

### 时间复杂度

- 斜着扫描：O(n^2)

### C++ 代码

```cpp
#include <iostream>
using namespace std;
const int N = 1e3 + 10;
typedef long long LL;

int t, c[N][N], n;

LL solve() {
    LL ans = 0;
    for (int d = -(n - 1); d <= n - 1; d++) {
        LL sum = 0;
        for (int i = 0; i < n; i++) {
            int j = i + d;
            if (j < 0 || j >= n) continue;
            sum += c[i][j];
        }
        ans = max(sum, ans);
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> c[i][j];
            }
        }
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
```

## C. Combination_Lock

### 算法 - 中位数+滑动窗口

- 如果没有 wrapping 条件的话，直接选中位数作为最终目标即可，类似[货仓选址](https://www.acwing.com/problem/content/description/106/)
- 带上 wrapping 条件的话，相当于是一个环形的货仓选址问题了，首先将每个数都加上 `n` 并排序，想象成这 `w` 个数组成一个环，枚举最优方案所有可能的断开方法，然后再求中位数对应的距离差之和最小值即可。
- 在任意地方断开的话，还要增删元素显得特别麻烦，一种套路是把排序后的数组整体加上 `n`（源于这个题的 wrapping 条件），再复制一份到原数组末尾，然后使用滑动窗口枚举长度为 `w` 的窗口，等价于枚举不同的切开方式。这个套路在蓝书 P75 最小表示法有讲，对于这种环形切分特别有用。

例子（Sample 2）：

```txt
2 3 8 9 2+n 3+n 8+n 9+n
```

- 需要用大小为 w 的滑动窗口求中位数，并求每个点到中位数的距离之和，暴力法肯定是每次直接求和，但是这样总时间复杂度 O(w^2) 将无法承受
- 关键是要 O(1) 时间算出区间内的总距离，可以发现当前窗口距离和其实是可以由滑动之前的窗口转移的

```bash
# 滑动之前
[x0, ..., xt]，中位数 x[t/2]
# 滑动之后
[x1, ..., x{t+1}]，中位数 x[(t+2)/2] = x[t/2+1]
```

减少的距离：

- A. `x0` 被抛弃了：`dist(x0, x[t/2])`
- B. 右侧的点都减小了：`dist(x[t/2], x[t/2]+1) * cnt`
  - `w` 为偶数，`cnt = w/2`；w 为奇数 `cnt = w/2`

增加的距离：

- C. `x{t+1}` 被加上了：`dist(x{t+1}, x[t/2+1])`
- D. 左侧的点都增加了：`dist(x[t/2], x[t/2]+1) * cnt`
  - `w` 为偶数，`cnt = w/2 - 1`；w 为奇数 `cnt = (w+1)/2 - 1`；可以统一为 `(w-1)/2`

Sample 2 里面 `w = 4`, `n = 10`，因此：

```txt
t = 3, x[t/2] = x[1], x[t/2+1] = x[2]
```

第一次的距离和 = 1 + 0 + 5 + 6 = 12

```txt
A = 1
B = 10
C = 4
D = 5
-(A + B) + C + D = -2
```

第二次的距离和 = 5 + 0 + 1 + 4 = 10

恰好满足 12+(-2)=10

### 时间复杂度

- 排序：O(w log w)
- 滑动窗口距离之和计算：O(w)

### C++ 代码

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;
const int W = 1e5 + 10;

int t, w, n;
LL x[2 * W];

LL solve() {
    LL ans = 1e18, pre, cur;
    for (int l = 0; l < w; l++) {
        int r = l + w;
        int mid = (l + r - 1) >> 1;
        if (l == 0) {
            cur = 0;
            for (int i = l; i < r; i++) {
                cur += abs(x[i] - x[mid]);
            }
            ans = min(ans, cur);
            pre = cur;
        } else {
            LL a = abs(x[l - 1] - x[mid - 1]);
            LL b = w / 2 * abs(x[mid - 1] - x[mid]);
            LL c = abs(x[r - 1] - x[mid]);
            LL d = (w - 1) / 2 * abs(x[mid - 1] - x[mid]);

            cur = pre - a - b + c + d;
            ans = min(ans, cur);
            pre = cur;
        }
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> w >> n;
        for (int i = 0; i < w; i++) {
            cin >> x[i];
            x[i + w] = x[i] + n;
        }
        sort(x, x + 2 * w);

        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
```

## D. Merge_Cards

- 跟[石子合并](https://www.acwing.com/problem/content/description/284/)差不多，都是区间 dp，`dp[i][j]` 表示闭区间 `[i, j]` 的平均得分
- 和石子合并的区别是，这里我们 dp 表示的不再是最大/最小，而是平均值，本质上都是一样的
- 需要维护前缀和 `sum`，用来快速求 `i~j` 的区间和

对于 Sample 1：

```txt
dp 1  2  3
1  0  3  13 + (3+11)/2
2     0  11
3        0
```

- 直接转移的话，时间复杂度是 `O(n^3)`，肯定是过不了 test 3 的
- 但是从 dp 矩阵来看，每个点要加的值就是它左边所有的值和他下面所有的值，维护这个和即可
- `N * A = 5 * 10^12`，爆 `int`，需要用 `long long`

### 时间复杂度

- 优化后的区间动态规划：O(n ^ 2)

### C++ 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 5e3 + 10;
typedef long long LL;

int t, n;
LL a[N], sum[N];
double dp[N][N], Left[N][N], down[N][N];

// 暴力解法
double solve_cubic() {
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = sum[j] - sum[i - 1];
            double tmp = 0, cnt = 0;
            for (int k = i; k + 1 <= j; k++) {
                tmp += dp[i][k] + dp[k + 1][j];
                cnt++;
            }
            dp[i][j] += tmp / cnt;
        }
    }
    return dp[1][n];
}

// 优化解法
double solve() {
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = sum[j] - sum[i - 1];
            double tmp = Left[i][j] + down[i][j];
            int cnt = j - i;
            dp[i][j] += tmp / cnt;
            Left[i][j + 1] = Left[i][j] + dp[i][j];
            down[i - 1][j] = down[i][j] + dp[i][j];
        }
    }
    return dp[1][n];
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            sum[i] = sum[i - 1] + a[i];
        }
        printf("Case #%d: %lf\n", i, solve());
    }
    return 0;
}
```
