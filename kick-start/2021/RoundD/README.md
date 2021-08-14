# Google KickStart 2021 Round D

- Score: 46
- Rank: 1393
- 开场服务器崩了，比赛时评测器巨慢，加时了 1 小时
- 总体来说应该是今年目前为止最难的一次了，最后一题一看就知道是线段树，但是多了个 `s` 又不知道怎么维护
    - Test 1 的答案居然是维护 `S` 个线段树，因为 `S` 很小，没想到这么复杂，出乎意料了
- 第 1 题就 WA 了好几次，最开始 `a+c` 为奇数的边界情况又没有考虑到

## A. Arithmetic Square

### 题目大意

- 9 宫格正中间缺了一个数，要求你填上一个数使得横、竖、斜着产生的等差数列最多。

### 算法 —— 分类讨论

- 已经确定是否为等差数列的有
    - left column, right column
    - top row, bottom row
- 中间的数 `G[1][1]` 可能构成的等差数列有 4 种情况:
    - top left diagonal
    - top right diagonal
    - middle column
    - middle row
- 计算这 4 种情况两端元素的和，如果是偶数 `s`，那么 `G[1][1]` 填 `s/2` 的话就会构成一个等差数列
- 用一个 map 存一下不同 `s` 的出现次数即可，选择出现次数最多的那个 `s`，按这个来填 `G[1][1]` 能够保证生成的等差数列尽量的多。
- 时间复杂度: `O(1)`

### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n, g[3][3];

int solve() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) continue;
            cin >> g[i][j];
        }
    }
    int ans = 0;
    // 已经确定的 4 中情况
    if (g[0][0] + g[0][2] == 2 * g[0][1]) ans++;
    if (g[2][0] + g[2][2] == 2 * g[2][1]) ans++;
    if (g[0][0] + g[2][0] == 2 * g[1][0]) ans++;
    if (g[0][2] + g[2][2] == 2 * g[1][2]) ans++;

    map<int, int> s;
    // top left
    s[g[0][0] + g[2][2]]++;
    // 竖着
    s[g[0][1] + g[2][1]]++;
    // top right
    s[g[0][2] + g[2][0]]++;
    // 横着
    s[g[1][0] + g[1][2]]++;
    int tmp = 0;
    for (auto& x : s) {
        // 选择出现次数最多的偶数和作为等差数列的首尾
        if (x.first % 2 == 0 && x.second > tmp) {
            tmp = x.second;
        }
    }
    return ans + tmp;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}

```

## B. Cutting Intervals

### 题目大意

- 给定 `N` 个区间，可以进行最多 `C` 次在某个整数点剪断的操作，要求最后的区间总数尽量地多

### 算法 —— 离散化+排序

- 对于 Test 1 来说，可以直接暴力求解
    - 对于每个闭区间区间 `[L, R]`，将区间内的元素 `(L, R)` 的值加 1，表示切这个点将要增加的新线段数，称为这个点的价值，时间复杂度 `O(NR)`
    - 将这些点按照价值从大到小排序，依次切直到次数 `>= C` 为止，时间复杂度 `O(R log R + C)`
    - 时间复杂度: `O(R(N + log R) + C)`
- 对于  Test 2 来说，上面的复杂度显然是太大了一些，但是注意到总的区间个数只有 `N = 1e5` 个，因此可以考虑使用离散化结合差分来降低时间复杂度
    - 初始的时候，差分数组都为 0，表示没有区间上所有的点没有被任何线段覆盖
    - 输入一个区间 `[L, R]`，就可以认为区间 `(L, R)` 上所有的值都需要加 1，因此可以通过 `diff[L+1] += 1, diff[R] -= 1` 来实现，处理一个输入只需要 `O(1)` 时间
    - 根据离散化之后的值，可以把整个数轴分成 `O(N)`（离散化之后端点值的总数）个区域，对这些区域按照价值进行排序，依次切直到次数 `>= C` 为止，注意对于区间 `[A， B)`，每次直接切 `min(B-A, C_remain)` 次，其中 `C_remain` 表示剩下的可以使用的切的次数。
    时间复杂度: `O(N log N)`

### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

typedef long long LL;

int t, n, m;
LL c, l[N], r[N], a[4 * N], diff[4 * N], cnt[4 * N];

// 查询 x 映射为哪个 [0, m) 之间的整数
int query(LL x) {
    return lower_bound(a, a + m, x) - a;
}
LL solve() {
    cin >> n >> c;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        a[4 * i] = l[i], a[4 * i + 1] = r[i];
        a[4 * i + 2] = l[i] + 1, a[4 * i + 3] = r[i] - 1;
    }
    // 离散化
    sort(a, a + 4 * n);
    m = unique(a, a + 4 * n) - a;
    for (int i = 0; i < m; i++) diff[i] = 0;
    // 预处理差分数组
    for (int i = 0; i < n; i++) {
        // 开区间 (L, R) 的覆盖次数都 +1
        diff[query(l[i] + 1)] += 1;
        diff[query(r[i])] -= 1;
    }
    // 差分数组求和得到每个点处的覆盖次数
    cnt[0] = diff[0];
    for (int i = 1; i < m; i++) {
        cnt[i] = cnt[i - 1] + diff[i];
    }
    // 按照覆盖次数从大到小对坐标进行排序
    vector<int> idx;
    for (int i = 0; i < m; i++) idx.push_back(i);
    sort(idx.begin(), idx.end(), [](int i, int j) {
        return cnt[i] > cnt[j];
    });
    LL ans = n;
    // 按照被区间覆盖次数从大到小来切
    for (int i = 0; i < m && c; i++) {
        int j = idx[i];
        if (j + 1 >= m) continue;
        // 左开右闭区间 [a[j], a[j+1])
        LL d = a[j + 1] - a[j];
        // 区间上每个点都可以切 1 次，获得 cnt[j] 个新区间
        LL tmp = min(d, c) * cnt[j];
        ans += tmp, c -= min(d, c);
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}

```

## C. Final Exam

### 题目大意

- 给定一组学生，能力值确定
- 给定一组题目集，每个题目集的所有题目的难度是一个区间，多个区间不会相交
- 对于每个学生，按照输入顺序依次分配最符合这个学生能力的题目给他，如果两个题目难度和他能力差值的绝对值一样，优先分配较简单的题目

### 算法 —— 用 map 维护不相交区间

- 对于 Test 1 来说，可以直接暴力求解
    - 遍历所有的区间，将区间内的数保存在一个 set 中，时间复杂度 `O(B log B)`
    - 对于每一个学生，都在 set 中查找最近的较小和较大的难度的题目，选择这两者中的最优的那个题目，时间复杂度 `O(M log B)`
    - 总时间复杂度为 `O((M+B) log B)`
- 对于 Test 2 来说，由于 `B` 的范围达到了 `1e18`，但是注意到最多只有 `N` 个区间，我们可以通过维护区间信息而不是将区间上所有数都做维护来减少时间复杂度
    - 直接按照题解的思路，区间用 map 维护，key 是区间起点，value 是区间终点
    - 对于每个输入 `s`，查找 `upper_bound` 区间后 `[x, y]`，分 3 中情况进行讨论
        1. `k = 1`，查到的区间是第 1 个区间，肯定就选这个区间最小值了
        2. 如果 `s in [l, r]`，`[l, r]` 是 `[x, y]` 的左边一个区间，那么需要将 `[l, r]` 区间拆分成两个区间
        3. 如果 `s > r`，需要根据情况判定应该使用 `r` 这个题目还是 `x` 这个题目
    - 总时间复杂度: `O(N log N + M O(log (N+M)))`
    - 注意：
        - 这里用 `lower_bound` 也可以，只是要多讨论一种 `s` 正好落在 `x` 的情况
        - 也可以用 `set<pair>` 来维护

### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

typedef long long LL;

int t, n, m;
LL s;
// key: 区间起点, value: 区间终点
map<LL, LL> intervals;

void add(LL a, LL b) {
    if (a <= b)
        intervals.insert({a, b});
}
void solve() {
    cin >> n >> m;
    intervals.clear();
    for (int i = 0; i < n; i++) {
        LL A, B;
        cin >> A >> B;
        intervals[A] = B;
    }
    for (int i = 0; i < m; i++) {
        cin >> s;
        auto it = intervals.upper_bound(s);
        auto [x, y] = *it;
        LL ch;
        if (it == intervals.begin()) {
            ch = x;
            intervals.erase(it);
            add(x + 1, y);
        } else {
            auto it1 = it;
            it1--;
            auto [l, r] = *it1;
            if (s <= r) {
                ch = s;
                intervals.erase(it1);
                add(l, s - 1);
                add(s + 1, r);
            } else {
                auto u = abs(r - s), v = abs(x - s);
                // 相等，选难度小的题目
                if (u <= v) {
                    ch = r;
                    intervals.erase(it1);
                    add(l, r - 1);
                } else {
                    ch = x;
                    intervals.erase(it);
                    add(x + 1, y);
                }
            }
        }
        cout << ch << " ";
    }
    cout << endl;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}

```

## D. Primes and Queries

### 题目大意

- 指数提升定理: http://www.zyymat.com/wp-content/uploads/2020/07/index-lifting.pdf, 里面有对题中 `V` 这个函数的定义
    - 在 `P` 整除 `a-b` 但是不整除 `a` 和 `b` 本身的情况下
    - 里面主要有 `P=2` 和 `P` 为奇质数两种情况
        - `P=2` 并且 `n` 为偶数，那么: `V(a^n - b^n) = V(a-b)+V(a+b)+V(n)-1`
        - 其他情况 `V(a^n - b^n) = V(a-b)+V(n)`
- 题目给出了典型的单点修改、区间查询问题，需要用线段树维护一下

### 算法 —— 多个线段树

- 对于 Test 1，直接维护 `S` 个线段树，每个线段树维护一个 `S` 的对应的公式值即可，普通的线段树问题，比较容易实现
- 对于 Test 2，需要使用质数提升定理的性质来做
    - 过于麻烦，之后有空再做一下
