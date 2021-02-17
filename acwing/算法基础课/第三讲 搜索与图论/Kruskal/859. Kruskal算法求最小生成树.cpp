/*
Kruskal 是加边的算法，用到了并查集维护生成森林的所有点，时间复杂度为 O(M log M)
*/
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 10, M = 2e5 + 10;

struct P {
    int x, y, z;
    bool operator<(const P& b) {
        return z < b.z;
    }
} edge[M];
int fa[N], n, m, ans;
int get(int x) {
    if (x == fa[x]) return x;
    return fa[x] = get(fa[x]);
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].x >> edge[i].y >> edge[i].z;
    }
    sort(edge + 1, edge + m + 1);
    // 并查集初始化
    for (int i = 1; i <= n; i++) fa[i] = i;
    // 求最小生成树
    for (int i = 1; i <= m; i++) {
        int x = get(edge[i].x);
        int y = get(edge[i].y);
        if (x == y) continue;
        fa[x] = y;
        ans += edge[i].z;
    }
    // 可以逐一判断是否则一个集合
    // y 总则是看看上面的循环是不是 merge 了 n-1 次
    for (int i = 2; i <= n; i++) {
        if (get(i) != get(1)) {
            puts("impossible");
            return 0;
        }
    }
    cout << ans << endl;
    return 0;
}