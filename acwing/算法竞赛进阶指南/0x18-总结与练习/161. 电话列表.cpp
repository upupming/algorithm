/*
Trie 树
先排序排序
然后一直插入即可，后续过程跟「前缀统计」就是一样的了
如果发现之前已经有过就输出 Yes
*/
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e6 + 10, M = 1e4 + 10;

int trie[N][10], t, n, tot = 1, cnt[N];
string strs[M];
// Trie 模板
bool insert(string &s) {
    int len = s.length(), p = 1;
    bool hasPrefix = 0;
    for (int k = 0; k < len; k++) {
        int ch = s[k] - '0';
        if (trie[p][ch] == 0)
            trie[p][ch] = ++tot;
        p = trie[p][ch];
        if (cnt[p]) hasPrefix = 1;
    }
    cnt[p]++;
    return hasPrefix;
}
int main() {
    cin >> t;
    while (t--) {
        memset(trie, 0, sizeof trie);
        memset(cnt, 0, sizeof cnt);
        tot = 1;

        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> strs[i];
        }
        sort(strs, strs + n);
        bool yes = 1;
        for (int i = 0; i < n; i++) {
            if (insert(strs[i])) {
                puts("NO");
                yes = 0;
                break;
            }
        }
        if (yes)
            puts("YES");
    }
    return 0;
}