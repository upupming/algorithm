/*
二分图染色问题
大于一个数的所有的边，能够构成一个二分图，那么这个数就是答案
可以用二分来做
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 2e4 + 10, M = 2e5 + 10;

int n, m;
int head[N], ver[M], edge[M], Next[M], tot;
int color[N];
// 加入有向边 (x, y)，权值为 z
void add(int x, int y, int z) {
    // 真实数据
    ver[++tot] = y, edge[tot] = z;
    // 在表头 x 处插入
    Next[tot] = head[x], head[x] = tot;
}
bool dfs(int u, int c, int mid) {
    color[u] = c;
    // 访问从 x 出发的所有边
    for (int i = head[u]; i; i = Next[i]) {
        int y = ver[i], z = edge[i];
        // 找到了一条有向边 (x, y)，权值为 z
        if (z <= mid) continue;
        if (color[y]) {
            if (color[y] == color[u]) return false;
        } else {
            if (!dfs(y, 3 - c, mid)) return false;
        }
    }
    return true;
}
// 只允许使用权重 >= mid 的边，能否构成二分图
bool valid(int mid) {
    memset(color, 0, sizeof color);
    for (int i = 1; i <= n; i++) {
        if (!color[i])
            if (!dfs(i, 1, mid)) return false;
    }
    return true;
}
int main() {
    cin >> n >> m;
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    int l = 0, r = 1e9;
    while (l < r) {
        int mid = l + r >> 1;
        if (valid(mid))
            r = mid;
        else
            l = mid + 1;
    }
    cout << r << endl;
    return 0;
}