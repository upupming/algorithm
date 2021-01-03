/*
枚举回文子串的中心，按长度分奇偶讨论，二分 p, q 即可
长度为奇数：[i-p, i] == [i, i+p]，长度为 2p + 1
长度为偶数：[i-q+1, i] == [i+1, i+q]，长度为 2q
*/
#include <iostream>
using namespace std;
const int P = 131;

typedef unsigned long long LL;

string s;
int cnt;
LL f[1000010], g[1000010], p[1000010];
LL getHash(int l, int r) {
    return f[r] - f[l - 1] * p[r - l + 1];
}
LL getReverseHash(int l, int r) {
    return g[l] - g[r + 1] * p[r - l + 1];
}
bool validOdd(int i, int p) {
    int l = i - p, r = i + p;
    return getHash(l, i) == getReverseHash(i, r);
}
bool validEven(int i, int q) {
    int l = i - q + 1, r = i + q;
    return getHash(l, i) == getReverseHash(i + 1, r);
}
int main() {
    while (cin >> s && s != "END" && ++cnt) {
        p[0] = 1;
        int n = s.length();
        for (int i = 1, j = n; i <= n; i++, j--) {
            f[i] = f[i - 1] * P + (s[i - 1] - 'a' + 1);
            g[j] = g[j + 1] * P + (s[j - 1] - 'a' + 1);
            p[i] = P * p[i - 1];
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int pl = 0, pr = min(i, n - 1 - i);
            while (pl < pr) {
                int mid = (pl + pr + 1) >> 1;
                if (validOdd(i + 1, mid))
                    pl = mid;
                else
                    pr = mid - 1;
            }
            ans = max(ans, 2 * pl + 1);
            int ql = 0, qr = min(i + 1, n - 1 - i);
            while (ql < qr) {
                int mid = (ql + qr + 1) >> 1;
                if (validEven(i + 1, mid))
                    ql = mid;
                else
                    qr = mid - 1;
            }
            ans = max(ans, 2 * ql);
        }
        cout << "Case " << cnt << ": " << ans << endl;
    }
    return 0;
}