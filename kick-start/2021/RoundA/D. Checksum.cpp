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
