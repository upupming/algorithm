# Google KickStart 2021 Round B

比 A 轮还是难一点，只拿了 37 分，再接再厉。

- Score: 37
- Rank: 1946

## A. Increasing Substring

### 算法 —— 线性扫描

- 从前到后扫描整个字符串，`dp[i]` 表示以 `i` 为结尾的最长单调子串的长度
- 转移方程为：

    $$
    \begin{cases}
        dp(i) = dp(i) + 1, & s[i] > s[i-1] \\
        dp(i) = 1, & s[i] \le s[i-1] \\
    \end{cases}
    $$
- 由于状态计算只需要使用上一个下标 `dp[i-1]` 的值，所以将数组可以优化成一个变量，滚动更新。

### 时间复杂度

- 扫描一遍字符串: $O(n)$

### C++ 代码

```cpp
#include <iostream>
using namespace std;

int t, n, k;
string s;

void solve() {
    int dp = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] > s[i - 1])
            dp += 1;
        else
            dp = 1;
        cout << dp << " ";
    }
    cout << endl;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> s;
        s = ' ' + s;
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}

```

## B. Longest Progression

比较复杂的一个分类讨论，当时没有梳理清楚逻辑关系，直接在 2020 RoundE Problem A 的基础上写的暴力（暴力枚举差分改变的地方，然后运行原来的朴素算法），$O(N^2)$ 的所以会在 Test 2 上 TLE。

### 算法 —— 差分+贪心

- 计算最长等差数列和 2020 RoundE Problem A 一样，是首先计算差分数组，然后统计差分数组里面最长的相同数组成的子串的长度 `len`，答案就是 `len+1`
    - 例如: 原数组 `A=[1,3,4,7,9,11]`，差分数组 `D=[2,1,3,2,2]`（其中 `D[i] = A[i+1]-A[i], i = 1,...n-1`），最长相同数子串 `[2,2]`，长度为 2，对应最长等差数列为 `[7,9,11]`，长度为 3
- 现在可以在原来的基础上修改一个数，修改一个数等价于修改两个差分值
    - 不妨设你将 `A[i]` 增加 `x`，那么修改之后 `D[i-1]` 会增加 `x`，`D[i]` 会减少 `x`，两者的总和保持不变。这个修改对最终的差分数组的影响需要分情况讨论
    - 可以先将差分数组分成若干段，每一段都是一个包含全部一样数 `d` 的子串，不妨设起始下标为 `D[i]`，长度为 `k`
    - 我们一定是修改下个子串的第一个差分值让其等于当前子串的差分值，这样能使答案优于不改变任何数的时候的答案
    - 改变了子串的第一个差分值 `D[i+k]` 之后，会对紧接着的差分值 `D[i+k+1]` 产生影响，需要分情况考虑
    - 例子 1 (`D[i+k] + D[i+k+1] != 2d`): `D=[1,1],[3],[0,0]`，考虑第 1 个子串，修改第 2 个子串的第一个数之后就是: `D=[1,1],[1],[2,0]`，最终的 `len=3`
    - 例子 2 (`D[i+k] + D[i+k+1] == 2d, D[i+k+2] != d`): `D=[1,1],[2],[0,0]`，考虑第 1 个子串，修改第 2 个子串的第一个数之后就是: `D=[1,1],[1],[1,0]`，最终的 `len=4`
    - 例子 3 (`D[i+k] + D[i+k+1] == 2d, D[i+k+2] == d`): `D=[2],[1],[3],[2,2]`，考虑第 1 个子串，修改第 2 个子串的第一个数之后就是: `D=[2],[2],[2],[2,2]`，最终的 `len=5`

### 时间复杂度

- 预处理差分数组、按照相等值分段: `O(N)`
- 依次考虑每块，并且对于每一块，考虑上面 3 种情况: `O(N)`

### C++ 代码

- 实际实现时，没有必要存储每个子串的长度 `k`，可以通过 `upper_bound` 实现，用 `set` 只会增加一个 `log` 的时间复杂度
- 对于例子 `A=[1,0,1,1], D=[-1,1,0]`，最优解是修改第 1 和第 2 个差分值，为了避免特殊判断，将 D 反转重新算一遍取最大即可

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;

int t, n, a[N], d[N];

int solve() {
    for (int i = 1; i <= n - 1; i++) {
        d[i] = a[i + 1] - a[i];
    }
    // 每一个子串的起始下标
    set<int> startPos;
    for (int i = 1; i <= n - 1; i++) {
        if (i == 1 || d[i] != d[i - 1]) {
            // i 是一个新的分段的起点
            startPos.insert(i);
        }
    }
    // 哨兵
    startPos.insert(n);

    // 枚举所有的子串，尝试修改后面的子串的第 1 个值
    int m = startPos.size(), ans = 0;
    for (auto it = startPos.begin(); it != startPos.end(); it++) {
        int i = *it, val = d[i];
        if (i > n - 1) break;
        auto it2 = it;
        it2++;

        // j 是下一个子串的开头
        int j = *it2;
        // 区间 [i, j)
        int tmp = j - i;
        // 区间 [i, j]
        if (j <= n - 1) tmp++;
        // 区间 [i, j+1]
        if (j + 1 <= n - 1 && d[j] + d[j + 1] == 2 * val) {
            tmp++;

            if (j + 2 <= n - 1 && d[j + 2] == val) {
                int k = *startPos.upper_bound(j + 2);
                // 区间 [i, k)
                assert(k <= n && d[k - 1] == val);
                tmp = k - i;
            }
        }
        ans = max(ans, tmp);
    }
    return ans + 1;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        int ans1 = solve();
        reverse(a + 1, a + 1 + n);
        int ans2 = solve();
        printf("Case #%d: %d\n", i, max(ans1, ans2));
    }
    return 0;
}

```

## C. Consecutive Primes

比赛的时候想到了先用线性筛计算 `[1, sqrt(Z)]` 范围内的素数，然后二分小因子的算法，总时间复杂度为 $O(\sqrt{Z} + log cnt)$，其中 `cnt` 表示`[1, sqrt(Z)]` 范围内的素数总个数。显然无法过 Test 3。主要瓶颈在线性筛算法上。

> 注：根据 [lucifer1004](https://cp-wiki.vercel.app/tutorial/kick-start/2021B/#problem-c-consecutive-primes) 的解释，用线性筛也是可以过的，但是要将线性筛外提，所有的测试用例只运行一次线性筛。不过这是因为 KickStart 给的时间限制比较宽裕，我们赛后还是要追求最好的解法。

### 算法 —— 素数判断

- 官方给的例子反倒更加简单，不需要用素数筛，只需要用素数判定算法即可，比第 2 题更加好实现，关键在于利用了条件「两个素数因子是相邻的」
- 假设最终的答案是 `N` (`N <= Z`)，那么最终两个相邻素数因子一定是 3 种情况:
    - `sqrt(Z)` 左侧最大、`sqrt(Z)` 右侧最小，这两个素数之积如果小于 `Z`，那么一定是答案
    - 否则，`sqrt(Z)` 左侧最近的两个素数，这两个素数之积一定小于 `Z`
- 根据[素数的数学性质](https://en.wikipedia.org/wiki/Prime_gap)，可以知道 `Z=1e18, sqrt(Z)=1e9` 时，临近的质数之差的绝对值不会超过 282，直接暴力的枚举即可

### 时间复杂度

- 枚举三个数: $O(282 \times 3)$
    - 判断是否是质数: $\sqrt[4]{Z}$
- 总时间复杂度: $O(282 \times 3 \times \sqrt[4]{Z})$

### C++ 代码

```cpp
#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;
typedef long long LL;

int t;
LL z;

bool is_prime(LL x) {
    if (x <= 1) return false;
    for (LL i = 2; i <= x / i; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

LL solve() {
    LL x = sqrt(z), a, b, c;

    LL t = x;
    for (; !is_prime(t); t--) {
        ;
    }
    b = t--;

    // Z = 6 时，特殊情况，不存在第二小的质因子 a
    if (t < 2) {
        a = z;
    } else {
        for (; !is_prime(t); t--) {
            ;
        }
        a = t;
    }

    t = x + 1;
    for (; !is_prime(t); t++) {
        ;
    }
    c = t;

    if (b * c <= z) return b * c;
    if (a * b <= z) return a * b;
    assert(false);
    return -1;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> z;
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}

```

## D. Truck Delivery

TODO
