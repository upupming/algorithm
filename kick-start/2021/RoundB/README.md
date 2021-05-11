# Google KickStart 2021 Round B

- [Google KickStart 2021 Round B](#google-kickstart-2021-round-b)
    - [A. Increasing Substring](#a-increasing-substring)
        - [算法 —— 线性扫描](#算法--线性扫描)
        - [时间复杂度](#时间复杂度)
        - [C++ 代码](#c-代码)
    - [B. Longest Progression](#b-longest-progression)
        - [算法 —— 差分+贪心](#算法--差分贪心)
        - [时间复杂度](#时间复杂度-1)
        - [C++ 代码](#c-代码-1)
    - [C. Consecutive Primes](#c-consecutive-primes)
        - [算法 —— 素数判断](#算法--素数判断)
        - [时间复杂度](#时间复杂度-2)
        - [C++ 代码](#c-代码-2)
    - [D. Truck Delivery](#d-truck-delivery)
        - [暴力解法](#暴力解法)
            - [算法 —— DFS + 暴力](#算法--dfs--暴力)
            - [时间复杂度](#时间复杂度-3)
            - [C++ 代码](#c-代码-3)
        - [优化解法](#优化解法)
            - [算法 —— DFS + 线段树](#算法--dfs--线段树)
            - [时间复杂度](#时间复杂度-4)
            - [C++ 代码](#c-代码-4)
    - [总结](#总结)

比 A 轮还是难一点，只拿了 37 分，思维和代码熟练度都欠缺，再接再厉。

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

- 计算最长等差数列和 2020 RoundE Problem A 一样，是首先计算差分数组，然后统计差分数组里面最长的具有相同数的子串的长度 `len`，答案就是 `len+1`
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

比赛的时候想到了先用线性筛计算 `[1, sqrt(Z)]` 范围内的素数，然后二分小因子的算法，总时间复杂度为 $O(\sqrt{Z} + \log cnt)$，其中 `cnt` 表示`[1, sqrt(Z)]` 范围内的素数总个数。显然无法过 Test 3。主要瓶颈在线性筛算法上。

> 注：根据 [lucifer1004](https://cp-wiki.vercel.app/tutorial/kick-start/2021B/#problem-c-consecutive-primes) 的解释，用线性筛也是可以过的，但是要将线性筛外提，所有的测试用例只运行一次线性筛。不过这是因为 KickStart 评测机的时间限制比较宽裕，我们赛后还是要追求最好的解法。

### 算法 —— 素数判断

- 官方给的解析反倒更加简单，不需要用素数筛，只需要用素数判定算法即可，比第 2 题更加好实现，关键在于利用了条件「两个素数因子是相邻的」
- 假设最终的答案是 `N` (`N <= Z`)，那么最终两个相邻素数因子一定是 3 种情况:
    - `sqrt(Z)` 左侧最大、`sqrt(Z)` 右侧最小，这两个素数之积如果小于 `Z`，那么一定是答案
    - 否则，`sqrt(Z)` 左侧最近的两个素数，这两个素数之积一定小于 `Z`
- 根据[素数的数学性质](https://en.wikipedia.org/wiki/Prime_gap)，可以知道 `Z=1e18, sqrt(Z)=1e9` 时，临近的质数之差的绝对值不会超过 282，直接暴力的枚举即可
- 这样看来，第三题比第二题是线上还简单很多，主要是有需要一个思维上的转变

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

### 暴力解法

> 暴力解法只能过 Test 1

#### 算法 —— DFS + 暴力

- DFS 一遍，计算每个点的到 1 的简单路径，记录 `pre` 数组，这里使用常用的遍历无向树的套路：dfs 参数 `x` 表示正在遍历的节点, `father` 记录从哪个方向来的，下一个节点不是 `father` 的时候往下遍历
- 初始化答案 `ans=0`，对于每一个查询，枚举路径上所有的点，依次比较每条边 `l` 值和当前查询的 `w`，看是否要更新答案 `ans = gcd(ans, a)`。

#### 时间复杂度

- DFS: $O(N)$
- 遍历所有询问: $O(Q)$
    - 每个询问需要访问路径上所有的边，最坏情况下最长边为 $N-1$: $O(N)$
        - 最多每条边计算一次 gcd
    - 计算 N 个数的 gcd 的总时间复杂度为 $O(N + \log(\max{A}))$，注意不是 $O(N \times \log(\max{A}))$，证明先略去
- 总时间复杂度: $O(Q(N + \log(\max{A})))$

#### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10, Q = 1e5 + 10;
typedef long long LL;

int t, n, q, pre[N];
vector<int> e[N];
unordered_map<int, unordered_map<int, LL>> L, A;

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

void dfs(int x, int fa) {
    pre[x] = fa;
    for (auto &y : e[x]) {
        if (y != fa) {
            dfs(y, x);
        }
    }
}

void solve() {
    memset(pre, -1, sizeof pre);
    dfs(1, -1);
    while (q--) {
        int c, w;
        cin >> c >> w;
        LL ans = 0;
        while (c != 1) {
            LL l = L[c][pre[c]], a = A[c][pre[c]];
            if (w >= l) {
                ans = gcd(ans, a);
            }
            c = pre[c];
        }
        cout << ans << " ";
    }
    cout << endl;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> q;
        for (int i = 1; i <= n; i++) e[i].clear();
        L.clear(), A.clear();
        for (int i = 0; i < n - 1; i++) {
            LL x, y, l, a;
            cin >> x >> y >> l >> a;
            e[x].push_back(y);
            e[y].push_back(x);
            L[x][y] = L[y][x] = l;
            A[x][y] = A[y][x] = a;
        }
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}

```

### 优化解法

#### 算法 —— DFS + 线段树

- 基于离线查询进行优化，按照特定顺序填充答案，降低时间复杂度
- 在 DFS 的过程中维护一个表示当前路径的线段树
    - 线段树的 key 为每条边的 load `l`
        - 这里有一个很重要的点，是说，所有的 `l` 是不同的（启发我们题目的数据范围一定要要仔细看），这就避免出现一个 key 有多个 value 的情况发生
    - 线段树的 value 为每条边的 amount `a`，初始值为 0 表示不存在
        - 删除的时候也是直接将 value 置为 0
    - 线段树的 merge 方式为 `gcd()`
- 在 DFS 搜索到 `x` 的时候，如果查询中存在当前节点 `x`，且负重为 `w`，只需要在线段数中查询所有 `<=w` 区间范围内的 `l` 的所有 `a` 值的 `gcd()`

#### 时间复杂度

- DFS: $O(N + Q)$
    - 同时维护线段树:
        - 维护的时间复杂度为 $\log(\max{L})$
        - 最多只需要计算 $\log(\max{L})$ 个数的 gcd: $O(\log(\max{L}) + \log(\max{A}))$
- 总时间复杂度: $O\left[(N + Q)(\log(\max{L}) + \log(\max{A}))\right]$

#### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10, Q = 1e5 + 10, LMax = 2e5 + 10;
typedef long long LL;

int t, n, q;
vector<int> e[N];
// 节点 x 的所有询问: pair<w, index>
vector<pair<int, int>> query[N];
unordered_map<int, unordered_map<int, int>> L;
unordered_map<int, unordered_map<int, LL>> A;
LL ans[Q];

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

struct SegmentTree {
    int l, r;
    LL dat;
} tree[LMax * 4];

// 线段树的建树，时间复杂度：O(N)
// p 表示节点编号，[l, r] 表示节点所代表的区间
void build(int p, int l, int r) {
    tree[p].l = l, tree[p].r = r;
    // 叶节点，表示单个元素
    if (l == r) {
        tree[p].dat = 0;
        return;
    }
    int mid = (l + r) >> 1;
    // 左子节点：编号为 2*p，代表区间 [l, mid]
    build(2 * p, l, mid);
    // 右子节点：编号为 2*p+1，代表区间 [mid+1, r]
    build(2 * p + 1, mid + 1, r);
    // 从下往上合并更新信息
    tree[p].dat = gcd(tree[2 * p].dat, tree[2 * p + 1].dat);
}

// 线段树的单点修改，时间复杂度：O(log N)
// 将 a[x] 的值修改为 v
void change(int p, int x, LL v) {
    // 找到叶节点
    if (tree[p].l == tree[p].r) {
        tree[p].dat = v;
        return;
    }
    int mid = (tree[p].l + tree[p].r) >> 1;
    // x 属于左半区间
    if (x <= mid) change(2 * p, x, v);
    // x 属于右半区间
    else
        change(2 * p + 1, x, v);
    // 从下往上合并更新信息
    tree[p].dat = gcd(tree[2 * p].dat, tree[2 * p + 1].dat);
}

// 线段树的区间查询，时间复杂度：O(log N)
// 查询序列 a 在区间 [l, r] 上的 gcd
LL ask(int p, int l, int r) {
    // 查询区间 [l, r] 完全包含节点 p 所代表的的区间
    if (l <= tree[p].l && r >= tree[p].r) return tree[p].dat;
    int mid = (tree[p].l + tree[p].r) >> 1;

    LL val = 0;
    // 左子节点 [tree[p].l, mid] 与查询 [l, r] 有重合
    if (l <= mid) val = gcd(val, ask(2 * p, l, r));
    // 右子节点 [mid+1, tree[p].r] 与查询 [l, r] 有重合
    if (r >= mid + 1) val = gcd(val, ask(2 * p + 1, l, r));
    return val;
}

void dfs(int x, int fa) {
    // assert 之前没有插入过 l，对应题目没有重复 l 的条件「All L_i are distinct.」
    assert(ask(1, L[x][fa], L[x][fa]) == 0);
    change(1, L[x][fa], A[x][fa]);
    // 回答所有对 x 的查询
    for (auto &[w, idx] : query[x]) {
        ans[idx] = ask(1, 0, w);
    }
    for (auto &y : e[x]) {
        if (y != fa) {
            dfs(y, x);
        }
    }
    change(1, L[x][fa], 0);
}

void solve() {
    memset(tree, 0, sizeof tree);
    memset(ans, 0, sizeof ans);
    build(1, 0, LMax);
    for (int i = 1; i <= n; i++) query[i].clear();
    for (int i = 1; i <= q; i++) {
        int c, w;
        cin >> c >> w;
        query[c].push_back(make_pair(w, i));
    }
    dfs(1, -1);
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> q;
        for (int i = 1; i <= n; i++) e[i].clear();
        L.clear(), A.clear();
        for (int i = 0; i < n - 1; i++) {
            int x, y, l;
            LL a;
            cin >> x >> y >> l >> a;
            e[x].push_back(y);
            e[y].push_back(x);
            L[x][y] = L[y][x] = l;
            A[x][y] = A[y][x] = a;
        }
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}

```

## 总结

1. 思路比较乱的时候，先不要实现，不然徒劳无功。真不行了，可以先实现朴素算法，再做改进。
2. 没有明确思路的时候，先把所有的题目看完，可能出现后面的题目更简单的情况。（这次都没有留下时间仔细想最后一题）
3. 数据范围还是需要仔细看。
