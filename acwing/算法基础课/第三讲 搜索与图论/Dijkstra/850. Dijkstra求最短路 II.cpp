/*
邻接表模板 + Dijkstra 模板

因为 N 达到 10^5，朴素方法会 TLE，需要使用堆优化的 Dijkstra 算法
*/
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 2e5 + 10, M = 2e5 + 10;
typedef pair<int, int> PII;

int head[N], ver[M], edge[M], Next[M], d[N];
bool v[N];
int n, m, tot;
// 为了让 pq 以距离排序，需要 PII.first 存储距离
priority_queue<PII, vector<PII>, greater<PII>> pq;
void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
}
void dijkstra() {
    memset(d, 0x3f, sizeof d);
    d[1] = 0;
    pq.push({0, 1});
    while (pq.size()) {
        // 取出堆顶
        int x = pq.top().second;
        pq.pop();
        if (v[x]) continue;
        v[x] = 1;
        // 扫描所有出边
        for (int i = head[x]; i; i = Next[i]) {
            int y = ver[i], z = edge[i];
            if (d[y] > d[x] + z) {
                d[y] = d[x] + z;
                pq.push({d[y], y});
            }
        }
    }
}
int main() {
    cin >> n >> m;
    // 构建邻接表
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        add(x, y, z);
    }
    dijkstra();
    cout << (d[n] == 0x3f3f3f3f ? -1 : d[n]) << endl;
    return 0;
}