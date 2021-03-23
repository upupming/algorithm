/*
trie 数，在每个插入的串末尾加一个 is_end 标记，dfs 到这里的时候直接返回这个子树的大小，这个子树都不满足条件
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 60, P = 110, M = N * P;
typedef long long LL;

int t, n, p;
int trie[M][2], tot = 1, is_end[M];
void insert(string& s) {
    int q = 1;
    for (auto& c : s) {
        int d = (c == 'R' ? 0 : 1);
        if (!trie[q][d]) trie[q][d] = ++tot;
        q = trie[q][d];
    }
    is_end[q] = 1;
}
LL dfs(int q, int dep) {
    if (is_end[q])
        return 1ll << (n - dep);
    LL ans = 0;
    if (trie[q][0])
        ans += dfs(trie[q][0], dep + 1);
    if (trie[q][1])
        ans += dfs(trie[q][1], dep + 1);
    return ans;
}
LL solve() {
    while (p--) {
        string s;
        cin >> s;
        insert(s);
    }
    return (1ll << n) - dfs(1, 0);
}
int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> p;
        tot = 1;
        memset(trie, 0, sizeof trie);
        memset(is_end, 0, sizeof is_end);
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
