/*
存在负权回路：
等价于从 1 到 x 的最短路径的边数 >= n，也就是说总点数 >= n+1，因为图中总共只有 n 个点，因此必定出现了一个环

由于需要加入所有点作为起点，时间复杂度 O(NM)
*/
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

using namespace std;
const int N = 1e5 + 10, M = 1e5 + 10;

int head[N], ver[M], edge[M], Next[M], d[N];
int n, m, tot, cnt[N];
bool v[N];
queue<int> q;
void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
}
bool spfa() {
    // d 数组无需初始化，因为我们最终需要求的不是真正的距离

    // 因为要求所有可能的负环，所以所有点都当做起点加进去
    for (int i = 1; i <= n; i++) {
        v[i] = 1;
        q.push(i);
    }

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
                cnt[y] = cnt[x] + 1;
                if (cnt[y] >= n) return true;
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
    cout << (spfa() ? "Yes" : "No") << endl;
    return 0;
}