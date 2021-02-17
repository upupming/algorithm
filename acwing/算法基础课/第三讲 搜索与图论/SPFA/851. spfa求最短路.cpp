/*
数据范围 N 和 M 均到了 10^5 的级别，只能使用平均情况为 O(M) 时间复杂度的 SPFA 算法
*/
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 1e5 + 10, M = 1e5 + 10;

int head[N], ver[M], edge[M], Next[M], d[N];
int n, m, tot;
bool v[N];
queue<int> q;
void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
}
void spfa() {
    memset(d, 0x3f, sizeof d);
    d[1] = 0, v[1] = 1;
    q.push(1);
    while (q.size()) {
        // 取出队头
        int x = q.front();
        q.pop();
        v[x] = 0;
        // 扫描所有出边
        for (int i = head[x]; i; i = Next[i]) {
            int y = ver[i], z = edge[i];
            if (d[y] > d[x] + z) {
                // 更新，把新的二元组插入堆
                d[y] = d[x] + z;
                if (!v[y]) q.push(y), v[y] = 1;
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
    // 单源最短路
    spfa();
    if (d[n] == 0x3f3f3f3f)
        puts("impossible");
    else
        cout << d[n] << endl;
    return 0;
}