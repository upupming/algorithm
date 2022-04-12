/*
暴力的方法：优先队列 BFS，二元组 (x, dist)，直接不断取出最小二元组，然后沿着从 x 出发的所有边进行拓展。由于是求第 K 短路，每个节点最多出队 K 次，可以将 visited 数组从 bool 变成 int 计数即可，时间复杂度为 O(K * (N + M) * log (N+M))
A*算法优化思路：估计距离 f(x) 定为从 x 到 T 的最短路长度，一定满足 f(x) <= g(x)（g(x) 是第 K 短路中从 x 到 T 的长度）
为了求 f(x)，需要先以 T 为起点，图中所有的边都反向，做一遍 BFS (Dijkstra 算法)
还有一个优化：出队超过 K 次的节点求的是大于 K 的最短路长度，到 T 的第 K 短路一定不经过这条路。
*/
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
// 因为要存一个反向图用来算 f，所以 M 要乘以 2
const int N = 1e3 + 10, M = (1e5 + 10) * 2;
typedef pair<int, int> PII;

// 邻接表模板
int head[N], rHead[N], ver[M], edge[M], Next[M], tot;
int n, m, a, b, l, s, t, k;
void add(int *h, int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z;
    Next[tot] = h[x], h[x] = tot;
}
int f[N], v[N];
void dijkstra() {
    memset(f, 0x7f, sizeof(f));
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push({0, t});
    f[t] = 0;
    while (q.size()) {
        auto now = q.top();
        q.pop();
        if (v[now.second]) continue;

        v[now.second] = 1;
        f[now.second] = now.first;
        for (int i = rHead[now.second]; i; i = Next[i]) {
            int y = ver[i], w = edge[i];
            if (v[y]) continue;
            if (now.first + w < f[y]) {
                q.push({now.first + w, y});
            }
        }
    }
}
void aStar() {
    memset(v, 0, sizeof(v));
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push({f[s], s});
    while (q.size()) {
        auto now = q.top();
        q.pop();
        // cout << now.second << " " << now.first << " " << now.first - f[now.second] << endl;

        // 之前已经访问过 k 次了，现在一定是第 k + 1 次访问
        if (v[now.second] >= k) continue;

        int d = now.first - f[now.second];
        if (
            // 至少包含一条边，才有可能 v++
            // 例子中有 s == t 的情况，但是 s 第一次出队列并不是一条路径
            d > 0 && ++v[now.second] == k && now.second == t) {
            cout << d << endl;
            return;
        }

        for (int i = head[now.second]; i; i = Next[i]) {
            int y = ver[i], w = edge[i];
            if (v[y] >= k) continue;
            // cout << now.second << ", " << y << ", " << d + w << endl;
            q.push({d + w + f[y], y});
        }
    }
    cout << -1 << endl;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> l;
        add(head, a, b, l), add(rHead, b, a, l);
    }
    cin >> s >> t >> k;
    dijkstra();
    aStar();
    return 0;
}