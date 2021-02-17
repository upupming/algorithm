/*
Prim 采用加点的思想，时间复杂度为 O(N^2)，堆优化版为 O(M log N)，适用于稠密图，一般直接用朴素版即可
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 510;

int n, m, a[N][N], d[N], ans;
bool v[N];
void prim() {
    memset(d, 0x3f, sizeof d);
    d[1] = 0;
    for (int i = 1; i < n; i++) {
        int x = 0;
        for (int j = 1; j <= n; j++) {
            if (!v[j] && (x == 0 || d[j] < d[x]))
                x = j;
        }
        v[x] = 1;
        for (int y = 1; y <= n; y++) {
            // 注意这里是和 Dijkstra 的区别所在，求的是到集合的距离，不需要加 d[x] 了
            // 这里可以求出生成树中 y 的前驱结点是谁
            if (!v[y]) d[y] = min(d[y], a[x][y]);
        }
    }
}
int main() {
    cin >> n >> m;
    memset(a, 0x3f, sizeof a);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        // 注意是无向图
        a[x][y] = a[y][x] = min(a[x][y], z);
    }

    prim();
    for (int i = 2; i <= n; i++) {
        if (d[i] == 0x3f3f3f3f) {
            puts("impossible");
            return 0;
        }
        ans += d[i];
    }
    cout << ans << endl;
    return 0;
}