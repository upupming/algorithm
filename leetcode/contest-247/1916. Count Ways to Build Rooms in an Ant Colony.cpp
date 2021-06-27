#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = N;
const int P = 1e9 + 7;
typedef long long LL;

int head[N], ver[M], Next[M], tot;
int f[N], g[N];
void add(int x, int y) {
    ver[++tot] = y;
    Next[tot] = head[x], head[x] = tot;
}
int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = (LL)ans * a % p;
        a = (LL)a * a % p;
        b >>= 1;
    }
    return ans;
}
int s[N], sz[N];
int dfs(int u) {
    sz[u] = 0;
    for (int i = head[u]; i; i = Next[i]) {
        int y = ver[i];
        dfs(y);
        sz[u] += sz[y];
    }
    s[u] = f[sz[u]];
    for (int i = head[u]; i; i = Next[i]) {
        int y = ver[i];
        s[u] = (LL)s[u] * g[sz[y]] % P * s[y] % P;
    }
    sz[u]++;
    return s[u];
}
class Solution {
   public:
    int waysToBuildRooms(vector<int>& prevRoom) {
        int n = prevRoom.size();
        tot = 0;
        // 点的标号为 [0, n-1]
        for (int i = 0; i < n; i++) {
            head[i] = 0;
        }
        for (int i = 1; i < n; i++) {
            add(prevRoom[i], i);
        }
        f[0] = g[0] = 1;
        for (int i = 1; i <= n; i++) {
            f[i] = (LL)f[i - 1] * i % P;
            g[i] = (LL)g[i - 1] * qpow(i, P - 2, P) % P;
        }
        return dfs(0);
    }
};
