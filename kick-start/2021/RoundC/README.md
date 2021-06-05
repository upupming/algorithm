# Google KickStart 2021 Round C

- Score: 19
- Rank: 3556
- A 题 WA 了，难受，没心思做后面题导致全部拉跨，只 AC 了 B 题
    - 写出正确的实现非常关键，不能再写 Bug 了

## A. Smaller Strings

### 算法 —— 按位枚举

- 类似数位 DP，枚举每一位的填法即可，用 `f[len]` 表示长为 `len` 的所有回文串（不必满足题目的小于条件）有多少，先预处理一遍。
- ok 表示第 `dep` 位可以填 `s[dep]` 而仍然保证小于关系（由于 `1~dep-1`位都已经确定，后半段回文也确定了，就算第 `dep` 位填 `s[dep]` 也可能可以保证小于关系）
- 边界情况需要格外注意，下面这个特殊例子，填 `baa` 之后，最后一位是可以填 `a` 的，因为 `reverse(baa)=aab < abd`，注意 `a`  相同所以延续到 `a<b` 来做比较，实际实现时通过 `ok` 的传递来实现

    ```txt
    7 5
    baaaabd
    ```

    - 比赛的时候想到了比较 `s[i]` 与 `s[n-1-i]`，但是没想到相同的时候需要延续到 `s[i-1]` 与 `s[n-i]`，构造很多测试用例也没构造到上面这个例子，所以就一直 WA
- 时间复杂度:
    - 预处理 `f`: `O(N)`
    - 枚举填充所有的位: `O(N)`
    - 总时间复杂度度：`O(N)`

### C++ 代码

```cpp
#include <algorithm>
#include <iostream>
typedef long long LL;
const int P = 1e9 + 7;
const int N = 1e5 + 10;

using namespace std;

int t;
LL n, k, f[N];
string s;

void prework() {
    f[0] = 1;
    for (LL i = 1; i <= n; i += 2) {
        f[i] = f[i + 1] = f[i - 1] * k % P;
    }
}

// ok 表示第 dep 位可以填 s[dep] 而仍然保证小于关系（由后半段回文保证了）
LL dfs(int dep, bool ok) {
    bool newOk = (s[dep] < s[n - 1 - dep] || (s[dep] == s[n - 1 - dep] && ok));
    if (dep == (n - 1) / 2) {
        if (n % 2 == 0) {
            return s[dep] - 'a' + newOk;
        } else {
            // 边界情况，奇数长回文只能用上一位的 ok
            return s[dep] - 'a' + ok;
        }
    }
    LL ans = 0;
    // 填 a~s[dep]-1
    if (n - 2 * (dep + 1) >= 0) {
        ans += (s[dep] - 'a') * f[n - 2 * (dep + 1)];
    }
    // 填 s[dep]
    ans += dfs(dep + 1, newOk);
    return ans % P;
}

LL solve() {
    prework();
    return dfs(0, false);
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> k >> s;
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}

```

## B. Alien Generator

### 算法 —— 暴力枚举

- 推公式可得: `k = (2g-i^2+i)/(2i)`，因此 `2g-i^2+i>0`，二次函数不等式解一下得到 `i` 的范围是 `[1-sqrt(1-8g)]/2` 到 `[1+sqrt(1-8g)]/2`，这个范围是 `sqrt(g)` 大小的，直接暴力枚举所有 `i` 判断求出的 `k` 是不是整数即可。
- 时间复杂度 `O(sqrt(G))`

```cpp
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
typedef long long LL;

using namespace std;

int t;
LL g;

LL solve() {
    LL ans = 0;
    double delta = sqrt(1 + 8 * g);
    LL start = floor((1 - delta) / 2), end = ceil((1 + delta) / 2);
    for (auto x = max(start, 1ll); x <= end; x++) {
        auto above = (2 * g - x * x + x), under = (2 * x);
        if (above % under == 0 && above / under > 0) {
            ans++;
        }
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> g;
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}

```

## C. Rock Paper Scissors

### 算法 —— 动态规划

- 题目说了一定有方案能够使答案大于等于 X (It is guaranteed that for given X a solution exists.)
- 可以直接 dp，求一下每天的 60 轮里面最高得分的方案即可，肯定就是答案，都不用验证是否 >= X（因为题目说了一定有解，最大的值肯定是满足 >= X 的）
- `dp[i][r][s][p]`:
    - 状态表示: 前 `1~i` 轮，我方有 `r` 轮出出 Rock，有 `s` 轮出 Scissors，有 `p` 轮出 Paper 的状态，最后一维 `p=i-r-s` 可以消去
    - 属性：最大平均得分
    - 状态计算: 根据当前的 `i, r, s, p`，可以推得对手出各种牌的概率，从而知道自己选各种方案的平均得分，从而进行转移（具体见代码注释）
    - 注意：一般来说 dp 可以枚举每一个状态可以由哪些状态转移过来，也可以枚举一个状态可以转移到哪些状态，在这个题目上，后者显然更加方便实现
- 记录下状态转移的路径，`ch[i][r][s]` 表示状态下最后一个方案是什么，可以由此反推上个状态直到初始态，最后输出方案即可
- 时间复杂度:
    - 枚举所有状态: `O(60^3)`
        - 状态转移: `O(1)`
    - 总时间复杂度: `O(60^3)`

### C++ 代码

```cpp
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;
const int N = 65;

int t, x;
double w, e;
char ch[N][N][N];
void solve() {
    // dp[i][r][s], p=i-r-s
    double dp[N][N][N] = {-1};
    // 第 1 轮出 r/s/p，平均得分都是 (w+e+0)/3
    dp[1][1][0] = dp[1][0][1] = dp[1][0][0] = (w + e) / 3;
    ch[1][1][0] = 'r', ch[1][0][1] = 's', ch[1][0][0] = 'p';
    for (int i = 1; i <= 60; i++) {
        for (int r = 0; r <= i; r++) {
            for (int s = 0; s + r <= i; s++) {
                int p = i - r - s;
                // 下一轮对手出 3 种牌的概率
                double pP = (double)r / i, pR = (double)s / i, pS = (double)p / i;
                // 下一轮我们分别出 r, s, p 的得分
                double rScore = pS * w + pR * e, sScore = pP * w + pS * e, pScore = pR * w + pP * e;

                if (dp[i + 1][r + 1][s] < dp[i][r][s] + rScore) {
                    ch[i + 1][r + 1][s] = 'r';
                    dp[i + 1][r + 1][s] = dp[i][r][s] + rScore;
                }
                if (dp[i + 1][r][s + 1] < dp[i][r][s] + sScore) {
                    ch[i + 1][r][s + 1] = 's';
                    dp[i + 1][r][s + 1] = dp[i][r][s] + sScore;
                }
                if (dp[i + 1][r][s] < dp[i][r][s] + pScore) {
                    ch[i + 1][r][s] = 'p';
                    dp[i + 1][r][s] = dp[i][r][s] + pScore;
                }
            }
        }
    }

    int ci = 60, cr, cs;
    double best = -1;
    // 求 i==60 时的最大
    for (int r = 0; r <= 60; r++) {
        for (int s = 0; r + s <= 60; s++) {
            if (dp[60][r][s] > best) {
                cr = r, cs = s;
                best = dp[60][r][s];
            }
        }
    }
    string ans;
    while (ci >= 1) {
        switch (ch[ci][cr][cs]) {
            case 'r':
                ans += 'R';
                cr--;
                break;
            case 's':
                ans += 'S';
                cs--;
                break;
            case 'p':
                ans += 'P';
                break;
        }
        ci--;
    }
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
}
int main() {
    cin >> t >> x;
    for (int i = 1; i <= t; i++) {
        cin >> w >> e;
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}

```

## D. Binary Operator

### 算法 —— 哈希+表达式求值

- 想到的是类似字符串哈希的算法，随机生成一些函数，通过多次随机检测，如果结果都相同，则认为是一类，试了一下果然过了
- 一开始认为每两对之间都是相等的，做 10 次测试（当然次数越多越好了，但是 10 次理论上就基本上不会出问题了），每次测试生成不同的 total function（就是将输入 x, y 映射成一个输出 z），在同一次测试中 total function 需要保持一致，不同测试中的 total function 则需要进行改变
- 剩下的就是表达式求值的模板，直接 copy 一下蓝书上[「表达式计算4」的源代码](https://github.com/upupming/algorithm/tree/master/acwing/算法竞赛进阶指南/0x18-总结与练习/151.%20表达式计算4.cpp)即可，这题还做了简化，没有负数，一个括号内也只会有一个运算符（即题目的 fully parenthesized 条件，因此可以省去优先级的判断）。
- 另外，需要牢固掌握高精度模板，这题用到了[高精度加高精度](https://github.com/upupming/algorithm/tree/master/acwing/算法基础课/第一讲%20基础算法/高精度/791.%20高精度加法.cpp)、[高精度乘高精度](https://github.com/upupming/algorithm/tree/master/acwing/算法基础课/第一讲%20基础算法/高精度/793.%20高精度乘法-高精度乘以高精度.cpp)。
- 时间复杂度：
    - 枚举 10 次 `(10)`
        - 枚举所有表达式 `O(N)`
            - 表达式求值 `O(N)`
            - 比较前面的所有表达式 `O(N)`
        - 两两比较 `O(N)` 构造分组答案
    - 总时间复杂度 `O(10N^2)`

### C++ 代码

```cpp
#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
const int N = 110;

int t, n, idx[N];
string e[N];
vector<int> val[N];
bool same[N][N];
unordered_map<string, unordered_map<string, vector<int>>> h;

int random(int n) {
    return (long long)rand() * rand() % n;
}

string toString(const vector<int> &A) {
    string ans;
    for (auto x : A) ans += to_string(x);
    return ans;
}
bool cmp(const vector<int> &A, const vector<int> &B) {
    if (A.size() != B.size()) {
        return A.size() < B.size();
    }
    for (int i = A.size() - 1; i >= 0; i--) {
        if (A[i] != B[i]) return A[i] < B[i];
    }
    return false;
}
void out(const vector<int> &A) {
    for (int i = A.size() - 1; i >= 0; i--) {
        cout << A[i];
    }
}
vector<int> add(const vector<int> &A, const vector<int> &B) {
    if (A.size() < B.size()) return add(B, A);
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size(); i++) {
        t += A[i];
        if (i < B.size()) t += B[i];
        C.push_back(t % 10);
        t /= 10;
    }
    if (t) C.push_back(t);
    return C;
}
vector<int> mul(const vector<int> &A, const vector<int> &B) {
    vector<int> C(A.size() + B.size());
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B.size(); j++) {
            C[i + j] += A[i] * B[j];
        }
    }
    int t = 0;
    for (int i = 0; i < C.size(); i++) {
        t += C[i];
        C[i] = t % 10;
        t /= 10;
    }
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}
vector<int> calc_hash(const vector<int> &A, const vector<int> &B) {
    vector<int> ans;
    auto a = toString(A), b = toString(B);
    if (h.count(a) && h[a].count(b)) return h[a][b];
    int c = random(INT_MAX);
    while (c > 0) {
        ans.push_back(c % 10);
        c /= 10;
    }
    return h[a][b] = ans;
}

vector<int> calc_exp(int i) {
    vector<int> ans;
    vector<vector<int>> nums;
    vector<char> ops;
    string s = e[i];
    int n = s.length();
    vector<int> val;
    for (int i = 0; i < n; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            val.push_back(s[i] - '0');
            if (i + 1 < n && s[i + 1] >= '0' && s[i + 1] <= '9') continue;
            reverse(val.begin(), val.end());
            nums.push_back(val);
            val.resize(0);
        } else if (s[i] == '(') {
            ops.push_back('(');
        } else if (s[i] == ')') {
            while (ops.size() && ops.back() != '(') {
                // 出栈一个符号就计算一下
                char op = ops.back();
                ops.pop_back();
                // 计算逻辑
                {
                    auto y = nums.back();
                    nums.pop_back();
                    auto x = nums.back();
                    nums.pop_back();
                    vector<int> z;
                    switch (op) {
                        case '+':
                            z = add(x, y);
                            break;
                        case '*':
                            z = mul(x, y);
                            break;
                        case '#':
                            z = calc_hash(x, y);
                            break;
                    }
                    // 把运算结果放回栈中
                    nums.push_back(z);
                }
            }
            // 左括号出栈（如果有的话）
            if (ops.size()) ops.pop_back();
        } else {
            // 运算符，直接入栈，这题简化了，括号内最多只有一个运算符
            ops.push_back(s[i]);
        }
    }
    return nums.front();
}

void solve() {
    // 开始认为两两之间都相等，需要经受 10 次考验，受不住的就设置为不相等
    memset(same, 1, sizeof same);
    // 随机生成 10 次 total function 进行消除
    for (int k = 0; k < 10; k++) {
        h.clear();
        for (int i = 1; i <= n; i++) {
            val[i] = calc_exp(i);
            // cout << i << " ";
            // out(val[i]);
            // cout << endl;
            for (int j = 1; j < i; j++) {
                // val[i] != val[j]
                if (cmp(val[i], val[j]) || cmp(val[j], val[i])) {
                    same[i][j] = same[j][i] = false;
                }
            }
        }
    }
    int p = 1;
    for (int i = 1; i <= n; i++) {
        bool found = false;
        for (int j = 1; j < i; j++) {
            if (same[j][i]) {
                found = true, idx[i] = idx[j];
            }
        }
        if (!found) {
            idx[i] = p++;
        }
        cout << idx[i] << " ";
    }
    cout << endl;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> e[i];
        }
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}

```
