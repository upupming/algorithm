#include <iostream>
using namespace std;
const int N = 1e6 + 10;

int trie[N][26], tot = 1, cnt[N], n, m;
string s, t;
// Trie 模板
void insert() {
    int len = s.length(), p = 1;
    for (int k = 0; k < len; k++) {
        int ch = s[k] - 'a';
        if (trie[p][ch] == 0) trie[p][ch] = ++tot;
        p = trie[p][ch];
    }
    cnt[p]++;
}
int search() {
    int len = t.length(), p = 1, ans = 0;
    for (int k = 0; k < len; k++) {
        p = trie[p][t[k] - 'a'];
        if (p == 0) return ans;
        ans += cnt[p];
    }
    return ans;
}
int main() {
    cin >> n >> m;
    while (n--) {
        cin >> s;
        insert();
    }
    while (m--) {
        cin >> t;
        cout << search() << endl;
    }
    return 0;
}