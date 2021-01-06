/*
每次扩展的代价是任意的，使用优先队列 BFS
用二元组 (city, fuel) 来表示每个状态，其中 city 为城市编号，fuel 为油箱中剩余的汽油量
d[city][fuel] 存储最少花费
起始状态 (S, 0)
状态 (city, fuel) 的分支：
1. 若 fuel < C，可以加一升汽油，扩展到新状态 (city, fuel+1)，花费在城市 city 加一升汽油的钱
2. 扩展边，若 (city, next) 边权 w 不超过 fuel，可以开车前往城市 next，扩展到新状态 (next, fuel - w)

注意双端队列BFS和优先队列BFS都是「出队」的时候进行拓展和 visited 标记

时间点
看书：11分钟
做完：55分钟

*/
#include <cassert>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
// 因为是无向图，M 一定要记得乘以 2，不然数组会越界！！
const int N = 1e3 + 10, M = 2 * (1e4 + 10), C = 110;

struct P {
    int city, fuel, cost;
    // 注意是最小堆
    bool operator<(const P &other) const {
        return cost > other.cost;
    }
};
int n, m, p[N], q, v[N][C], d[N][C];
// 邻接表模板
int head[N], ver[M], edge[M], Next[M], tot;
void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z;
    Next[tot] = head[x], head[x] = tot;
}
void solve(int c, int s, int e) {
    memset(v, 0, sizeof(v));
    memset(d, 0x7f, sizeof(d));
    priority_queue<P> q;
    q.push({s, 0, 0});
    d[s][0] = 0;
    while (q.size()) {
        auto now = q.top();
        q.pop();

        if (now.city == e) {
            cout << now.cost << endl;
            return;
        }
        if (v[now.city][now.fuel]) continue;
        v[now.city][now.fuel] = true;

        // 扩展
        // 加 1 升油
        if (now.fuel < c &&
            d[now.city][now.fuel + 1] > now.cost + p[now.city]) {
            d[now.city][now.fuel + 1] = now.cost + p[now.city];
            q.push({now.city, now.fuel + 1, now.cost + p[now.city]});
        }
        // 所有以 now.city 为起点的边
        int cnt = 0;
        for (int i = head[now.city]; i; i = Next[i]) {
            int y = ver[i], z = edge[i];
            // 如果可以开到，那么扩展到这个新的状态
            if (z <= now.fuel &&
                d[y][now.fuel - z] > now.cost) {
                d[y][now.fuel - z] = now.cost;
                q.push({y, now.fuel - z, now.cost});
            }
        }
    }
    cout << "impossible" << endl;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < m; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        add(u, v, d), add(v, u, d);
    }
    cin >> q;
    while (q--) {
        int c, s, e;
        cin >> c >> s >> e;
        solve(c, s, e);
    }
    return 0;
}