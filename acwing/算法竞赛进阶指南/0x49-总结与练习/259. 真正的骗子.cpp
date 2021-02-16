/*
好人总数：p1，坏人总数：p2
一个人要么是好人，要么是坏人
每个人 x 分成两个域 x_good 和 x_bad

两种查询：
- x y yes: 合并 x_good 和 y_good，合并 x_bad 和 y_bad
- x y no: 合并 x_good 和 y_bad，合并 x_bad 和 y_good

对于每一个人 x：
- 如果 x 在好人集合，那么任意满足 fa[y] == fa[x] 的 y 都是好人，fa[y] == fa[x_bad] 的 y 都是坏人
- 如果 x 在坏人集合，那么任意满足 fa[y] == fa[x] 的 y 都是坏人，fa[y] == fa[x_bad] 的 y 都是好人

dp[i][j]:
- 状态表示：前 i 个集合可以拼成 j 个好人的方法数，只有当 dp[集合个数][p1] == 1 时，能唯一确定谁是好人，谁是坏人
- 状态转移：
    - 如果第 i 个集合是好人，dp[i][j] += dp[i-1][j-集合的 root 是好人时好人人数]
    - 如果第 i 个集合是坏人，dp[i][j] += dp[i-1][j-集合的 root 是坏人时好人人数]

暂时没过
TODO: fix this
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 3 * 1010, M = 610;

int fa[N], sz[N], d[N], dp[M][M], tot, vis[N], good[N], bad[N];
void init() {
    for (int i = 0; i <= N; i++) {
        fa[i] = i;
        sz[i] = 1;
    }
    memset(dp, 0, sizeof dp);
    tot = 0;
    dp[0][0] = 1;
    memset(vis, 0, sizeof vis);
}
// Get 操作
int get(int x) {
    if (x == fa[x]) return x;
    // 路径压缩，fa 直接赋值为代表元素
    return fa[x] = get(fa[x]);
}
void merge(int x, int y) {
    int fx = get(x), fy = get(y);
    if (fx == fy) return;
    if (sz[fx] < sz[fy]) {
        fa[fx] = fy;
        sz[fy] += sz[fx];
    } else {
        fa[fy] = fx;
        sz[fx] += sz[fy];
    }
}

int n, p1, p2, x, y, m;
string s;
int main() {
    while (cin >> n >> p1 >> p2, n, p1, p2) {
        init();
        m = p1 + p2;
        for (int i = 1; i <= n; i++) {
            cin >> x >> y >> s;
            if (s[0] == 'y') {
                merge(x, y);
                merge(x + m, y + m);
            } else {
                merge(x, y + m);
                merge(x + m, y);
            }
        }

        for (int i = 1; i <= m; i++) {
            int fi = get(i);
            // 不是 root，跳过
            if (fi != i) continue;
            // 以 fi 为 root 的集合标记为被访问过了
            vis[fi] = vis[fi + m] = ++tot;
            // 记录一下集合大小
            good[tot] = sz[fi], bad[tot] = sz[fi + m];
            cout << i << " " << good[tot] << " " << bad[tot] << endl;
        }

        for (int i = 1; i <= tot; i++) {
            for (int j = min(good[i], bad[i]); j <= p1; j++) {
                // 第 i 个集合是好人
                if (j >= good[i])
                    dp[i][j] += dp[i - 1][j - good[i]];
                // 第 i 个集合是坏人
                if (j >= bad[i])
                    dp[i][j] += dp[i - 1][j - bad[i]];
            }
        }

        if (dp[tot][x] != 1) {
            puts("no");
            continue;
        }

        for (int i = tot; i; i--) {
            // 第 i 个集合可以是好人
            if (dp[i - 1][x - good[i]])
                p1 -= good[i], good[i] = -1;
            // 第 i 个集合可以是坏人
            else if (dp[i - 1][x - bad[i]])
                p1 -= bad[i], good[i] = -2;
        }

        for (int i = 1, fi = get(1); i <= m; fi = get(++i)) {
            if (vis[fi]) {
                if (fi > m && good[vis[i]] == -2)
                    cout << i << endl;
                else if (fi <= m && good[vis[i]] == -1)
                    cout << i << endl;
            }
        }
        puts("end");
    }
    return 0;
}