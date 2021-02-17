/*
Dijkstra 用来求边权为正值的单源最短路问题

Dijkstra 两个算法：
- 朴素：O(N^2)，适用于 M 比较大，N 很小的情况
- 堆优化：O(M log N)，适用于 N 比较大的情况

这个题目 N 的数据范围很小，因此，直接使用朴素的 Dijkstra 算法
由于存在重边，相同的起止点的边，只需要加入最短的那条就行，自环直接忽略
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 510;

int n, m, a[N][N], d[N];
bool v[N];
void dijkstra() {
    memset(d, 0x3f, sizeof d);
    d[1] = 0;
    // 重复 n - 1 次
    for (int i = 1; i < n; i++) {
        int x = 0;
        // 找到未标记节点中 dist 最小的
        for (int j = 1; j <= n; j++) {
            if (!v[j] && (x == 0 || d[j] < d[x]))
                x = j;
        }
        v[x] = 1;
        // 用全局最小值点 x 更新其他节点
        for (int y = 1; y <= n; y++)
            d[y] = min(d[y], d[x] + a[x][y]);
    }
}
int main() {
    cin >> n >> m;
    memset(a, 0x3f, sizeof a);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        a[x][y] = min(a[x][y], z);
    }
    dijkstra();
    cout << (d[n] == 0x3f3f3f3f ? -1 : d[n]) << endl;
    return 0;
}