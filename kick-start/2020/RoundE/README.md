# KickStart 2020 Round E 题解

## A. Longest_Arithmetic

### 算法 - 差分+最长相等子序列

- 题目要求最长的等差数列
- 先求差分数组 `d`
- 用 `dp[i]` 表示以 `d[i]` 为结尾的最长相等子数组长度
  - 如果 `d[i] == d[i-1]`，那么 `dp[i] = dp[i-1] + 1`，否则 `dp[i] = 1`
- 答案就是 `max_{i}{dp[i] + 1}`

### 时间复杂度

- 线性扫描：O(n)

### C++ 代码

```cpp
#include <iostream>
using namespace std;
const int N = 2e5 + 10;

int t, a[N], n, d[N], dp[N];

int solve() {
    // 注意如果 d[1] == d[2] 的话，是不能让 dp[2] = 2 的，只能认为有一个相等的差，因此需要特判
    dp[2] = 1;
    int ans = 2;
    for (int i = 3; i <= n; i++) {
        if (d[i] == d[i - 1])
            dp[i] = dp[i - 1] + 1;
        else
            dp[i] = 1;
        // cout << i << " " << d[i] << " " << dp[i] << endl;
        // 加一是因为有 x 个相等的差，那么等差数列的长度是 x + 1
        ans = max(ans, dp[i] + 1);
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            d[i] = a[i] - a[i - 1];
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}

```

## B. High_Buildings

### 算法 - 分类讨论

- 方案有很多，只需要构造一种合法的方案即可。
- `x = N - (A+B-C)` 表示两个人都看不见的数量，`x < 0` 的话，一定不能够满足
- 先把 `C` 个最高的放在正中央，放高度为其他的总不会优于放 N，因此就都定为高度 `N`
- 接下来：
  - 把 `A-C` 个 `N-1` 放在左边
  - 把 `B-C` 个 `N-1` 放在右边
- 这样总共放了 A+B-C 个看得见的了，接下来是 x 个看不见的
- 这样，看不见的直接插入到左边到正中央之间，高度为 `N-2` 即可；也可以直接插入到正中间到右边之间，高度为 `N-2`
- 需要特判的情况是：
  - `N-1 <= 0`，也就是 `N=1`，这种情况只能放 `N=1`，因此必须要求 `A=B=C=N=1`
  - `N-2 <= 0`，也就是 `N=2`，左右两边最低只能放 `N-1 = 1`，那么就必须要求 `x = 0`；而且只能是 `[1, 2]、[2, 2] 和 [2, 1]` 这三种情况

### 时间复杂度

- 枚举所有建筑：O(n)

### C++ 代码

```cpp
#include <cassert>
#include <iostream>
using namespace std;

int t, n, a, b, c;

bool solve() {
    int left, mid, right;
    int x = n - (a + b - c);
    if (x < 0) return false;

    if (n == 1) {
        if (a == 1 && b == 1 && c == 1) {
            cout << 1 << endl;
        } else
            return false;
    } else if (n == 2) {
        if (a == 2 && b == 1 && c == 1) {
            cout << 1 << " " << 2 << endl;
        } else if (a == 2 && b == 2 && c == 2) {
            cout << 2 << " " << 2 << endl;
        } else if (a == 1 && b == 2 && c == 1) {
            cout << 2 << " " << 1 << endl;
        } else {
            return false;
        }
    } else {
        mid = c, left = a - c, right = b - c;
        assert(left + mid + right + x == n);
        // 需要隐蔽，但是无缝可插
        if (left + mid + right <= 1 && x != 0) return false;
        // 插入到中央和右边之间
        int flag = 0;
        // 插入到中央和左边之间
        if (left > 0) flag = 1;
        // 插入到中央的第一根和第二根之间
        if (mid > 1) flag = 2;

        while (left--) cout << n - 1 << " ";
        if (flag == 1)
            while (x--) cout << n - 2 << " ";
        if (flag == 2) {
            cout << n << " ";
            mid--;
            while (x--) cout << n - 2 << " ";
        }
        while (mid--) cout << n << " ";
        if (flag == 0)
            while (x--) cout << n - 2 << " ";
        while (right--) cout << n - 1 << " ";
        cout << endl;
    }
    return true;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> a >> b >> c;
        printf("Case #%d: ", i);
        if (!solve()) {
            puts("IMPOSSIBLE");
        }
    }
    return 0;
}
```

## C. Toys

### 算法 - 贪心+优先队列

- `sum_e` 表示所有玩具的 `e` 的和
- 如果最终停在第 `i` 玩具的话，一定是第 2 轮，因为第 1 轮不可能停下（之前都没玩过），假设是在第 3 轮停下的话，那距离上次玩经过的时间一定是 `sum_e - e[i]`，也就是说 `sum_e - e[i] < r[i]`，满足这个条件的话，第 2 轮也一定会停下来的；同理，更不可能是在第 4, 5, ... 轮
- 判断能不能无限玩下去和计算删除最少使得玩的时间最长这两个问题需要用两趟来完成：

1. 能不能无限玩下去

    满足 `sum_e - e[i] < r[i]` 的玩具是一定会停下来的，因此我们优先删除不等号两边差异较大的玩具（因为一定会被删除，删除过程中 `sum_e` 也是在减小的），这就是贪心的思想，移一下项得到 `sum_e < e[i] + r[i]`，把玩具按照 e+r 从大到小排序，逐渐删除直到：

    1. 所有玩具都会停下来，删到只剩下最后一个玩具了，那么说明不可能无限玩下去
    2. 删到 `>= 2` 个玩具的时候，发现没有 `sum_e < e[i] + r[i]` 的玩具了，说明可以无限玩下去

2. 不能无限玩下去的话，计算最长玩的时间

    优先删除编号最小的不能满足玩具，因为这是唯一的可能增加玩的时长的方法，删除编号第 2 小的还是会卡在第 1 个停止

    删除之后前面可能产生新的不能玩的玩具，在产生的新的不能玩的玩具里面需要先删除 `e[i] + r[i]` 较大的类似上面的过程，因此要用优先队列维护，`first` 存一下标号

- `N * Ei = 10^14`，爆 `int`，需要用 `long long`

### 时间复杂度

- 排序：O(n log n)
- 优先队列：O(n log n)

### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
typedef pair<int, int> PII;

int t, n;
struct P {
    LL e, r, idx;
    bool operator<(const P& q) const {
        return e + r > q.e + q.r;
    }
} p[N];
bool cmp(P a, P b) {
    return a.idx < b.idx;
}
LL sum_e;

void solve() {
    // 1. 判断能否无限玩下去
    sort(p, p + n);
    for (int i = 0; i < n; i++) {
        // 删除当前最不满足的玩具
        if (sum_e < p[i].e + p[i].r) {
            sum_e -= p[i].e;
        } else {
            cout << i << " INDEFINITELY" << endl;
            return;
        }
    }
    // 2. 判断最长能玩多长的时间
    // 还原初始顺序
    sort(p, p + n, cmp);
    // 再求一遍 sum
    sum_e = 0;
    for (int i = 0; i < n; i++) sum_e += p[i].e;
    // 至少能够玩 1 轮，cur_cnt 表示当前删除数量，cur_ans 表示当前可玩时间
    LL ans = sum_e, cnt = 0, cur_ans = sum_e, cur_cnt = 0;
    priority_queue<PII> pq;
    // 按照编号从小到大遍历
    for (int i = 0; i < n; i++) {
        // 如果不能满足就删除
        if (sum_e < p[i].e + p[i].r) {
            cur_cnt++;
            sum_e -= p[i].e;
            // 只需要减去第一趟的时间，因为第二趟都没加上
            cur_ans -= p[i].e;
            // 看看前面有哪些会因为不满足而删掉
            while (pq.size() && sum_e < pq.top().first) {
                cur_cnt++;
                auto now = pq.top();
                pq.pop();
                sum_e -= p[now.second].e;
                // 玩的时间里面，第一趟和第二趟都要减去，第二趟在之前的循环里加上过
                cur_ans -= 2 * p[now.second].e;
            }
        } else {
            // 虽然现在满足，但是之后后面删掉之后可能不满足，先放进最大堆里
            pq.push({p[i].e + p[i].r, i});
            cur_ans += p[i].e;
            if (cur_ans > ans) {
                ans = cur_ans;
                cnt = cur_cnt;
            }
        }
    }
    cout << cnt << " " << ans << endl;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        sum_e = 0;
        for (int i = 0; i < n; i++) {
            cin >> p[i].e >> p[i].r;
            p[i].idx = i;
            sum_e += p[i].e;
        }
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
```

## D. Golden_Stone

- N 个点，M 条无向边，S 种石头，R 个菜单，将石头 (a1, ..., ak) 搬到同一点之后，可以变成一个新的石头 b。携带一个石头过一条边耗能 1，每次最多携带 1 个石头，石头可以暂存在任一点。求石头变成类别 1 需要的最小能量。
- 这道题比较难，因此直接参考了[吴自华大佬的题解](https://leetcode-cn.com/circle/article/M1wbLj/)。
- `cost[i][j]` 表示在第 `j` 个城市制造（或直接获得）一块第 `i` 种石头的代价
  - 转移方式 1：我们根据某一配方，在第 `j` 个城市制造出一种新石头 `s_k`。这样可以转移到状态 `(s_k,j)`。
  - 转移方式 2：我们带着这块石头去另一个城市 `c_k`。这样可以转移到状态 `(i,c_k)`。
- 利用 Dijkstra 算法，将 `(stone, city)` 看做状态，那些初始就有的石头 `cost` 初始化为 0，不断取出堆顶。Dijkstra 算法的性质可以保证，我们的方案一定是在 `j` 城市制作第 `r_i` 种配方的最优方案。

### 时间复杂度

- Dijkstra 中：
  - 点的数量 SN（石头总数 * 城市总数）
  - 边的数量：
    - RN，原图的 N 个点都会尝试用所有菜单
    - MS：边的数量（对于 N 个点的图边数为 M，但是我们是在 NS 个点的图上，边数为 MS）
- 复杂度：O((MS+RN)log(SN))

### C++ 代码

```cpp
// 代码来自：https://leetcode-cn.com/circle/article/M1wbLj/
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
typedef long long ll;
const ll INF = 1e12;

template <typename T>
void read(T &x) {
    x = 0;
    char c = getchar();
    T sig = 1;
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            sig = -1;
    for (; isdigit(c); c = getchar())
        x = (x << 3) + (x << 1) + c - '0';
    x *= sig;
}

class Solution {
    int n, m, s, r;

    int hash(int si, int ni) const { return si * (n + 1) + ni; };

   public:
    void solve(int case_num) {
        printf("Case #%d: ", case_num);
        read(n), read(m), read(s), read(r);
        vector<vector<int>> adj(n + 1), needed_by_recipe(s + 1);
        vector<vector<ll>> stone_cost(s + 1, vector<ll>(n + 1, INF)),
            recipe_cost(r, vector<ll>(n + 1));
        vector<vector<int>> ingredients_got(r, vector<int>(n + 1));
        vector<int> ingredients_need(r), product(r);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        for (int i = 0; i < m; ++i) {
            int u, v;
            read(u), read(v);
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }

        for (int city = 1; city <= n; ++city) {
            int stone_num;
            read(stone_num);
            for (int j = 0; j < stone_num; ++j) {
                int stone;
                read(stone);
                // cost[i][j]表示在第j个城市制造（或直接获得）一块第i种石头的代价
                stone_cost[stone][city] = 0;
                pq.push({0, hash(stone, city)});
            }
        }

        for (int i = 0; i < r; ++i) {
            read(ingredients_need[i]);
            for (int j = 0; j < ingredients_need[i]; ++j) {
                int ingredient;
                read(ingredient);
                // needed_by[i]记录第i种石头在哪些配方里被用到了（如果在某个配方里被用了多次，就记录多次）
                needed_by_recipe[ingredient].emplace_back(i);
            }
            read(product[i]);
        }
        // Dijkstra算法的性质可以保证，我们的这一方案，一定是在j城市制作第r_i种配方的最优方案。
        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();
            ll c = top.first;
            int u = top.second;
            int stone = u / (n + 1), city = u % (n + 1);
            if (c != stone_cost[stone][city])
                continue;
            for (int recipe : needed_by_recipe[stone]) {
                ingredients_got[recipe][city]++;
                // recipe_cost[ri][j]记录在第j个城市收集第r_i种配方的原料的成本
                ll nc = recipe_cost[recipe][city] += c;
                // 我们根据某一配方，在第jj个城市制造出一种新石头s_k。这样可以转移到状态(s_k,j)。
                if (ingredients_got[recipe][city] == ingredients_need[recipe]) {
                    if (nc < stone_cost[product[recipe]][city]) {
                        stone_cost[product[recipe]][city] = nc;
                        pq.push({nc, hash(product[recipe], city)});
                    }
                }
            }
            // 我们带着这块石头去另一个城市c_k。这样可以转移到状态(i,c_k)。
            for (int nxt : adj[city]) {
                if (c + 1 < stone_cost[stone][nxt]) {
                    stone_cost[stone][nxt] = c + 1;
                    pq.push({c + 1, hash(stone, nxt)});
                }
            }
        }
        ll ans = *min_element(stone_cost[1].begin(), stone_cost[1].end());
        printf("%lld\n", ans == INF ? -1 : ans);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    read(t);
    for (int i = 1; i <= t; ++i) {
        Solution solution = Solution();
        solution.solve(i);
    }
}
```
