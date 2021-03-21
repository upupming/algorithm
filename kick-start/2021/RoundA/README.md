# Google KickStart 2021 Round A

感觉本轮题目还是比较简单的，应该是第一次难度调小了一点，另外这次参加的人数大涨，报名总数接近两万人了。

很久没写优先队列 BFS，卡了很久，导致后面没时间想最后一题了（估计也想不出来），之后遇到这种情况马上看之前写的代码，不要自己想。

- Score: 56
- Rank: 2160

## A. K-Goodness String

### 算法

#### 遍历字符串

- `i` 从 `0` 开始递增，`j` 从 `n-1` 开始递减，求一下当前的 goodness，目标为 `k`，需要的改变次数最少为 `abs(goodness - k)`。
- 考试的时候忘记取 `abs`，过了 Sample 但是 WA 了一发。

#### 时间复杂度

- `O(N)`: 遍历字符串时间

### C++ 代码

```cpp
#include <iostream>
using namespace std;

int t, n, k;
string s;

int solve() {
    int good = 0;
    for (int i = 0, j = n - 1; i <= j; i++, j--) {
        if (s[i] != s[j]) good++;
    }
    return abs(k - good);
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> k;
        cin >> s;
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}

```

## B. L Shaped Plots

### 算法

#### 枚举 L 形中心点 + 二分

- L 形有八种不同的方向，如下所示，分别标号为 `0~7`，上下左右的坐标均是相对于中心点固定的，可使用 BFS 中常用的距离数组 `d` 来简化代码，我这里定义了 `dl`, `dr`, `du`, `dd`，表示四个点相对于中心点的偏移。

```txt
|    |
|    |
+-  -+

+-  -+
|    |
|    |


  |  |
--+  +--

--+  +--
  |  |
```

- 对于每个方向，二分 `L` 形的短边最远可以构成的距离 `d`，如果 `d >= 2`，那么所有满足条件 `L` 形的短边长可以取 `2, ..., d`，总共 `d - 1` 种方案。
- 在判断距离 `d` 能否构成 `L` 形时，计算左右点距离、上下点距离，看能否构成 2 倍关系，并且长为 `d` 和 `2d` 的边上全是数字 1，判断是否全是数字 1 可以用前缀和来判断。一条边上全是数字 1 当且仅当区间长度等于区间和。

#### 时间复杂度

- 枚举所有方向：`O(8)`
  - 枚举所有中心点：`O(RC)`
    - 二分求 `L` 形最大短边长：`O(log max{R, C})`
      - 判断是否合法：`O(1)`
- 总时间复杂度：`O(RC log {max(R, C)})`

### C++ 代码

```cpp
#include <iostream>
using namespace std;
const int N = 1e3 + 10;
typedef long long LL;

int t, g[N][N], r, c, sumR[N][N], sumC[N][N];

int dl[] = {0, -1, 0, -1, -2, 0, -2, 0};
int dr[] = {1, 0, 1, 0, 0, 2, 0, 2};
int du[] = {-2, -2, 0, 0, -1, -1, 0, 0};
int dd[] = {0, 0, 2, 2, 0, 0, 1, 1};

bool valid(int i, int j, int x, int dir) {
    int left = j;
    if (dl[dir] > 0)
        left = j + x * dl[dir] - 1;
    else if (dl[dir] < 0)
        left = j + x * dl[dir] + 1;

    int right = j;
    if (dr[dir] > 0)
        right = j + x * dr[dir] - 1;
    else if (dr[dir] < 0)
        right = j + x * dr[dir] + 1;

    int up = i;
    if (du[dir] > 0)
        up = i + x * du[dir] - 1;
    else if (du[dir] < 0)
        up = i + x * du[dir] + 1;

    int down = i;
    if (dd[dir] > 0)
        down = i + x * dd[dir] - 1;
    else if (dd[dir] < 0)
        down = i + x * dd[dir] + 1;

    if (up < 1 || right > c || left < 1 || down > r) return false;
    int h = abs(sumR[i][right] - sumR[i][left - 1]);
    int v = abs(sumC[j][down] - sumC[j][up - 1]);
    return ((h == x) &&
            (v == 2 * x)) ||
           ((h == 2 * x) &&
            (v == x));
}

LL calc(int dir) {
    LL ans = 0;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            int l = 0, right = max(r, c);
            while (l < right) {
                int mid = (l + right + 1) >> 1;
                if (valid(i, j, mid, dir)) {
                    l = mid;
                } else {
                    right = mid - 1;
                }
            }
            if (l < 2) continue;
            ans += l - 1;
        }
    }
    return ans;
}

LL solve() {
    LL ans = 0;
    for (int i = 0; i < 8; i++) {
        ans += calc(i);
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> r >> c;
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                cin >> g[i][j];
                sumR[i][j] = sumR[i][j - 1] + g[i][j];
                sumC[j][i] = sumC[j][i - 1] + g[i][j];
            }
        }
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}

```

## C. Rabbit House

### 算法

#### 优先队列 + flood fill

- 容易想到，最大的数不用变，周围比他小的数都要跟着改变到至多比他小 1
- 利用最大堆，将所有点入堆，初始值为 `g[i][j]`
- 每个点 `(i, j)` 第一次出堆时即为最终的 `g[i][j]` 值，并只在第一次出堆时进行扩展（通过标记 `v = 1` 实现）
- 扩展的时候，对于周围任意一个的点 `(x, y)`，至少变为 `g[i][j] - 1`，同时入堆
- 每个状态更新（入堆）多次、扩展（出堆）一次，第一次出堆时即为该状态的最小代价，当出堆总数达到矩阵大小时，即可返回答案。

#### 时间复杂度

- 优先队列 BFS: `O(RC log RC)`

### C++ 代码

```cpp
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 310;
typedef long long LL;
typedef pair<int, int> PII;

int t, g[N][N], r, c, v[N][N];
int maxV = 0, maxI, maxJ;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool valid(int x, int y) {
    return x >= 0 && x < r && y >= 0 && y < c;
}

struct P {
    int x, y, val;
    bool operator<(P b) const {
        return val < b.val;
    }
};

priority_queue<P> q;
LL solve() {
    if (maxV == 0) return 0;
    LL ans = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            q.push({i, j, g[i][j]});
        }
    }
    int cnt = 0;
    while (q.size()) {
        auto now = q.top();
        q.pop();
        if (v[now.x][now.y]) continue;
        v[now.x][now.y] = 1;
        if (++cnt == r * c) return ans;
        for (int k = 0; k < 4; k++) {
            int x = now.x + dx[k];
            int y = now.y + dy[k];
            if (!valid(x, y)) continue;
            int goal = g[now.x][now.y] - 1;
            if (g[x][y] < goal) {
                ans += goal - g[x][y];
                g[x][y] = goal;
            }
            q.push({x, y, g[x][y]});
        }
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> r >> c;
        maxV = 0;
        memset(v, 0, sizeof v);
        q = priority_queue<P>();
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cin >> g[i][j];
                if (g[i][j] > maxV) {
                    maxI = i, maxJ = j;
                    maxV = g[i][j];
                }
            }
        }
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}

```

## D. Checksum

### 算法

#### Kruskal 求最大生成树

- 首先明确一点，输入数据中 `R` 和 `C` 都是没用的，我们只要知道有这个结果在，相当于给矩阵 `A` 增加了限制条件，可以由 `A` 中已有的数和 `R`、`C` 反推未知的数。我们不需要求每个数的具体值，因此 `R` 和 `C` 是多少无关紧要（其实本题也无法求解，因为没有告诉你 `-1` 可以恢复成什么数）
- 矩阵元素的建图是常见的建图方法，将所有为 `-1` 的位置的行和列作为顶点，即二分图左侧点表示行，右侧点表示列，边权表示使用魔法恢复这个数的代价（即 `B[i][j]`）。
- 显然，二分图如果有环的话，环中一个点改变值，沿着环路上改变其他点的值，可以使得最终的行和列的异或结果不发生任何变化。
- 为了消除这些不确定性（无穷多解），我们需要定住某些点的值，等价于求一个生成树，留下的边就是不需要用魔法来恢复的 `(i, j)`，删除的边就是需要用魔法来恢复的。
- 为了最小化魔法的代价，我们需要求最大生成树的权值和，用所有边权和减去最大生成树权值和就是最小的魔法代价
- Kruskal 求最大生成树，只需要将求最小生成树时，边的排序改为从大到小即可

#### 时间复杂度

- 边排序：`O(N^2 log N)`
- Kruskal 算法：`O(N^2)`
- 总时间复杂度：`O(N^2 log N)`

### C++ 代码

```cpp
#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
using namespace std;
// 行数+列数=顶点数
const int N = 510 * 2, M = N * N;

int t, a[N][N], b[N][N], r[N], c[N], n;
int sum, fa[N], m;

struct P {
    int x, y, z;
    // 求最大生成树，所以边权从大到小排序
    bool operator<(const P& b) {
        return z > b.z;
    }
} edge[M];

int get(int x) {
    if (x == fa[x]) return x;
    return fa[x] = get(fa[x]);
}

int solve() {
    int ans = 0;
    sort(edge, edge + m);
    for (int i = 0; i < m; i++) {
        int x = get(edge[i].x);
        int y = get(edge[i].y);
        if (x == y) continue;
        fa[x] = y;
        ans += edge[i].z;
    }
    // 最大生成树是留下的边，删除的边就是付出的代价
    return sum - ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        m = sum = 0;
        cin >> n;
        // 并查集初始化
        for (int i = 0; i <= 2 * n; i++) fa[i] = i;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> b[i][j];
                if (a[i][j] == -1) {
                    // 行节点从 0 开始编号，列节点从 n 开始编号
                    // 边权为恢复代价
                    int x = i, y = j + n;
                    sum += b[i][j];
                    edge[m++] = {x, y, b[i][j]};
                }
            }
        }
        // 这道题中，r, c 是什么其实没有关系，KickStart 喜欢搞这种迷惑人
        for (int i = 0; i < n; i++) {
            cin >> r[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> c[i];
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}

```
