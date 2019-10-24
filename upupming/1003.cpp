#include <iostream>
#include <algorithm>

using namespace std;
#define MAX_VALUE 1000000000

int n, m, c1, c2;
int teams[505], adj[505][505], d[505], accTeams[505], cnt[505];
bool visited[505];

// 算法导论中的 Extract-Min 操作通常直接由一个循环来得到，使用队列无法在数据改变之后自动整理。

void relax(int u, int v, int w) { 
    if (d[v] == d[u] + w) {
        // cout << "previous path: d[v] = " << d[v] << ", cnt[v] = " << cnt[v] << endl;
        cnt[v] = cnt[v] + cnt[u]; // 除了自己原来的走法，再加上 u 的走法总数
        accTeams[v] = max(accTeams[v], accTeams[u] + teams[v]);
    } else if (d[v] > d[u] + w) {
        d[v] = d[u] + w;
        cnt[v] = cnt[v] + cnt[u]; // 除了自己原来的走法，再加上 u 的走法总数
        accTeams[v] = accTeams[u] + teams[v]; // 只有这一种走法
    }
}

void solve() {
    d[c1] = 0; accTeams[c1] = teams[c1];
    cnt[c1] = 1; // 自己本来就有一种走法
    while (true) {
        int u = -1, minD = MAX_VALUE;
        // Extract-Min
        for (int i = 0; i < n; i++) {
            if (!visited[i] && d[i] < minD) {
                minD = d[i];
                u = i;
            }
        }
        if (u == -1) break;
        visited[u] = true;
        for (int i = 0; i < n; i++) {
            // cout << "adj[" << u << "][" << i << "] = " << adj[u][i] << endl;
            if (!visited[i] && adj[u][i] != MAX_VALUE) relax(u, i, adj[u][i]);
        }
    }
    cout << cnt[c2] << " " << accTeams[c2] << endl;
}

int main() {
    cin >> n >> m >> c1 >> c2;
    for (int i = 0; i < n; i++) cin >> teams[i];
    int a, b, w;
    fill(*adj, *adj + 505 * 505, MAX_VALUE);
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        adj[a][b] = adj[b][a] = w;
    }
    fill(d, d + n, MAX_VALUE);
    solve();
    return 0;
}