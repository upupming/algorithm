/*
多个有向图的 SG 函数要取异或和，和 Nim 游戏的证明是一样的
*/
#include <cstring>
#include <iostream>
#include <unordered_set>
using namespace std;
const int N = 110, M = 1e4 + 10;

int n, m;
int s[N], f[M];

int sg(int x) {
    if (f[x] != -1) return f[x];
    unordered_set<int> S;
    for (int i = 0; i < m; i++) {
        if (x >= s[i]) S.insert(sg(x - s[i]));
    }
    for (int i = 0;; i++) {
        if (!S.count(i)) return f[x] = i;
    }
}

int main() {
    cin >> m;
    for (int i = 0; i < m; i++) cin >> s[i];
    cin >> n;
    memset(f, -1, sizeof f);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ans ^= sg(x);
    }
    if (ans)
        puts("Yes");
    else
        puts("No");
    return 0;
}
