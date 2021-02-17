/*
Bellman-Ford 算法，时间复杂度 O(NM)
for n次
    for 所有边 a,b,w (松弛操作)
        dist[b] = min(dist[b],back[a] + w)

SPFA 是队列优化版的 Bellman-Ford 算法，平均时间复杂度为 O(M)，在特殊构造的图上，会退化为 O(NM)，一般来说 SPFA 都优于 Bellman-Ford 算法

在求解有边数限制的最短路问题时，一般选择 Bellman-Ford 算法更好，最外层循环次数就是边数限制，此题就是具有边数限制的一个例子
*/
#include <cstring>
#include <iostream>
using namespace std;
const int M = 1e4 + 10, N = 510;

int n, m, k;
struct P {
    int x, y, z;
} e[M];
int d[N], last[N];
int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++)
        cin >> e[i].x >> e[i].y >> e[i].z;
    memset(d, 0x3f, sizeof d);
    d[1] = 0;
    for (int i = 1; i <= k; i++) {
        memcpy(last, d, sizeof d);

        for (int j = 1; j <= m; j++) {
            // 从上次的 last 距离转移，而不是这次的进行转移，否则边数多于 i 了
            d[e[j].y] = min(d[e[j].y], last[e[j].x] + e[j].z);
        }
    }
    // d[n] 虽然是无穷大，但是中间可能被一些负权值更新过，略小于 0x3f3f3f3f，其实也可以在 relax 的是时候做一个特判，无穷大的边不 relax 就行
    if (d[n] > 0x3f3f3f3f / 2)
        cout << "impossible" << endl;
    else
        cout << d[n] << endl;
    return 0;
}