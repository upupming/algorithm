/*
染色矛盾就说明不是二分图
时间复杂度：O(N+M)
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10, M = 2e5 + 10;

int head[N], ver[M], edge[M], Next[M], tot;
int n, m, v[N];
void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
}
bool dfs(int x, int color) {
    v[x] = color;
    for (int i = head[x]; i; i = Next[i]) {
        int y = ver[i];
        if (!v[y]) {
            if (!dfs(y, 3 - color)) return false;
        } else {
            if (v[y] == color) return false;
        }
    }
    return true;
}
bool isBipartite() {
    for (int i = 1; i <= n; i++) {
        if (!v[i]) {
            if (!dfs(i, 1)) return false;
        }
    }
    return true;
}
int main() {
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        add(u, v, 1), add(v, u, 1);
    }
    cout << (isBipartite() ? "Yes" : "No") << endl;
    return 0;
}