/*
异或可以看成是不进位的加法，因此可以利用前缀和获取到任意区间的异或和
对于前缀和: a[l] + ... + a[r] = s[r] - s[l-1]
对于异或和: a[l] ^ ... ^ a[r] = s[r] ^ s[l-1]
（注意: 异或对应的「减法」还是异或，因为如果 a^b=c，两边同时异或 b，得到 a=c^b）
现在就是要求所有 s[r] 与 s[l-1] 组成的异或对的最大值，转化为了最大异或对这一模板题，注意需要满足 r-l+1 <= m，需要从 trie 中动态地删除前面的元素（可以通过 cnt-- 实现）
*/
#include <iostream>
using namespace std;
const int N = 32 * 1e5 + 10, M = 1e5 + 10;

int n, m, a, s[M];
int trie[N][2], tot = 1, cnt[N];

void insert(int a, int v) {
    int p = 1;
    for (int i = 30; i >= 0; i--) {
        int j = a >> i & 1;
        if (trie[p][j] == 0) {
            trie[p][j] = ++tot;
        }
        p = trie[p][j];
        cnt[p] += v;
    }
}

int query(int a) {
    int ans = 0, p = 1;
    for (int i = 30; i >= 0; i--) {
        int j = a >> i & 1;
        if (cnt[trie[p][!j]]) {
            p = trie[p][!j];
            ans |= 1 << i;
        } else {
            p = trie[p][j];
        }
    }
    return ans;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        s[i] = s[i - 1] ^ a;
    }
    int ans = 0;
    insert(s[0], 1);

    for (int i = 1; i <= n; i++) {
        if (i > m) insert(s[i - m - 1], -1);
        int q = query(s[i]);
        // cout << i << " " << s[i] << " " << q << endl;
        ans = max(ans, q);
        insert(s[i], 1);
    }
    cout << ans << endl;
    return 0;
}
