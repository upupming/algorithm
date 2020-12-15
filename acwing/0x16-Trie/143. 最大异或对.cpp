/*
把每个数当成一个 32 位的二进制数，从前到后遍历 A[i] 的每一位，在 Trie 数中尽量找相反位的走法。
*/
#include <iostream>
using namespace std;
const int N = 32 * 1e5 + 10;

int trie[N][2], n, a, tot = 1, p, q;
int main() {
    cin >> n;
    int best = 0;
    while (n--) {
        cin >> a;
        p = q = 1;
        int ans = 0;
        for (int i = 31; i >= 0; i--) {
            int j = a >> i & 1;
            // cout << a << " " << i << " " << j << endl;
            if (trie[p][j] == 0) trie[p][j] = ++tot;
            p = trie[p][j];
            // 寻找匹配，能够匹配一个不同的位的话
            if (trie[q][!j]) {
                ans |= 1 << i;
                q = trie[q][!j];
            } else {
                q = trie[q][j];
            }
        }
        // cout << ans << endl;
        best = max(best, ans);
    }
    cout << best << endl;
    return 0;
}