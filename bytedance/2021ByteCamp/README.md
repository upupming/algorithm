# 2021 ByteCamp 夏令营笔试题目

- 时长 2 hours
- 可以用本地 IDE
- 感觉测试数据可能比较少（一提交马上就出结果了）
- 进去的时候系统提示说随机分发试卷，不知道是不是每个人的题目都有所不同，我这里分享一下我的题目。

## 最短的全集子串

### 题意

- 给一个小写字符串，找出最短的子串，其中包含这个字符串的所有字母
- 字符串长度 `N in [1, 65535]`

### 算法 —— 前缀和 + 二分

- 暴力解法，很显然，就是是枚举起点和终点，然后计算这一段中有多少不同的字母，时间复杂度为 `O(N^2)`
- 随着长度的增加，不同字母的数量一定是单调不减的，可以通过维护前缀和信息快速查找某个区间内任意一个字母的数量，例如 `sum[i][j]` 表示第 `i` 个字母在 `1~j` 的出现次数
- 先计算前缀和，然后枚举起始点，二分终止点即可
- 时间复杂度为 `O(N log N)`

### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5;

string s;
int sum[26][N], n;
int pos, len;
unordered_set<char> st;
bool valid(int i, int j) {
    int cnt = 0;
    for (int k = 0; k < 26; k++) {
        if (sum[k][j] - sum[k][i - 1] >= 1) {
            cnt++;
        }
    }
    return cnt == st.size();
}
int main() {
    cin >> s;
    n = s.length();
    s = ' ' + s;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            sum[j][i] = sum[j][i - 1];
            if (j == s[i] - 'a') {
                sum[j][i] += 1;
            }
        }
        st.insert(s[i]);
    }
    pos = 1, len = n;
    for (int i = 1; i <= n; i++) {
        int l = i, r = n;
        if (!valid(i, r)) continue;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (valid(i, mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        int newLen = l - i + 1, newPos = i;
        if (newLen < len) {
            pos = i;
            len = newLen;
        }
    }

    cout << pos - 1 << "," << len << endl;
    return 0;
}
/*
abbbaaccb
*/

```

## 马能否吃将

### 题意

- 给定棋盘大小不超过 30
- 给定 A 的马和将的坐标 `bx, by` 和 `dx, dy`
- B 的起始坐标为 `0, 0`，求 B 到达 `dx, dy` 吃将并且中途不可到达 A 的马的攻击范围的方案数，A 的马和将都保持不动（即不需要考虑两方都动的复杂情况，只是 B 不能到被 A 的马的攻击地方即可）
- 需要考虑蹩马腿的情况
- B 的马只允许向右上方移动

### 算法 —— 记忆化搜索

- 关键在于模拟整个过程，`dfs(x, y)` 表示从 `(x, y)` 到达 A 的将的方案数
- 需要注意在验证 A 的马能否攻击 B 的马的时候，注意 A 的马可以朝任意方向移动，不只是右上方
- 时间复杂度为 `O(N^2)`

### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 40;

int bx, by, dx, dy, v[N][N], cnt[N][N];
bool valid(int x, int y) { return x < N && y < N; }
bool equal(int x1, int y1, int x2, int y2) {
    return (x1 == x2) && (y1 == y2);
}
// 当前在 (cx, cy)， 可以走到的所有 (nx, ny)
void calc(int cx, int cy, vector<int> &nx, vector<int> &ny) {
    // 横着走
    if (!(equal(cx + 1, cy, bx, by)) && !(equal(cx + 1, cy, dx, dy)) && valid(cx + 2, cy + 1)) {
        nx.push_back(cx + 2);
        ny.push_back(cy + 1);
    }
    // 竖着走
    if (!(equal(cx, cy + 1, bx, by)) && !(equal(cx, cy + 1, dx, dy)) && valid(cx + 1, cy + 2)) {
        nx.push_back(cx + 1);
        ny.push_back(cy + 2);
    }
}
bool ok(int x, int y) {
    return (x == dx) && (y == dy);
}
bool canAttack(int x, int y) {
    return (!equal(bx + 1, by, dx, dy) && equal(bx + 2, by + 1, x, y)) ||
           (!equal(bx, by + 1, dx, dy) && equal(bx + 1, by + 2, x, y)) ||
           (!equal(bx - 1, by, dx, dy) && equal(bx - 2, by - 1, x, y)) ||
           (!equal(bx, by - 1, dx, dy) && equal(bx - 1, by - 2, x, y)) ||
           (!equal(bx, by - 1, dx, dy) && equal(bx + 1, by - 2, x, y)) ||
           (!equal(bx + 1, by, dx, dy) && equal(bx + 2, by - 1, x, y)) ||
           (!equal(bx - 1, by, dx, dy) && equal(bx - 2, by + 1, x, y)) ||
           (!equal(bx, by + 1, dx, dy) && equal(bx - 1, by + 2, x, y));
}
int dfs(int x, int y) {
    if (x >= 30 || y >= 30) return 0;
    if (canAttack(x, y)) return 0;
    // 之前访问过，已经记过数了，不再计数
    if (ok(x, y)) return 1;
    if (v[x][y]) return cnt[x][y];
    vector<int> nx, ny;
    calc(x, y, nx, ny);
    int ans = 0;
    for (int i = 0; i < nx.size(); i++) {
        ans += dfs(nx[i], ny[i]);
    }
    v[x][y] = 1;
    return cnt[x][y] = ans;
}
int main() {
    cin >> bx >> by >> dx >> dy;
    cout << dfs(0, 0) << endl;
    return 0;
}
/*
2 2 6 3
1 0 2 1
1 0 1 2
1 0 3 3
1 1 3 3
1 3 3 3
*/

```

## 最大染色值

### 题意

- 给定员工总数 `N`
- 给定 `D`、`E`、`F` 3 个数组表示第 `i` 个人分到衬衫 `D`、`E`、`F` 的高兴程度
- 要求总体高兴程度最大
- 给定上下级关系，例如 `0 1` 表示 `0` 是 `1` 的上级，要求直属上下级之间不能穿相同的颜色衬衫，上下级关系有 `N-1` 个，并且最大 boss 是 `0` 没有上级

### 算法 —— DFS 搜索

- 从最大 boss `0` 开始搜索
- 每次搜到 `cur`，不能和 `lastColor` 同色，遍历所有的下属，递归搜索每个下属的最大染色值，作和即可

### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5010;

int n, val[3][N];
vector<int> w[N];

int dfs(int cur, int fa, int lastColor) {
    int ans = 0;
    for (int color = 0; color < 3; color++) {
        if (color == lastColor) continue;
        int tmp = val[color][cur];
        for (auto& y : w[cur]) {
            if (y == fa) continue;
            tmp += dfs(y, cur, color);
        }
        ans = max(ans, tmp);
    }
    return ans;
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> val[0][i] >> val[1][i] >> val[2][i];
    }
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        w[x].push_back(y);
    }

    cout << dfs(0, -1, -1) << endl;
    return 0;
}
/*
3
2 4 9
1 3 5
1 2 3
0 1
0 2
*/

```
