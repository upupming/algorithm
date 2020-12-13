/*
F[i] 表示前缀子串 S[1-i] 的 Hash 值，有 F[i] = F[i-1] * P + (S[i] - "a" + 1)，P = 131 表示进制
区间 [l, r] 的 Hash 值为 F[r] - F[l-1] * 131^{r-l+1}
两个区间的 Hash 值相同时，即可认为两个字符串相等
时间复杂度 O(|S| + m)

注意手写快速幂（也可以在 dp 循环里面先预处理一个数组），用 unsigned long long 类型来处理溢出自动对 2^{64} 取模
*/
#include <iostream>
using namespace std;
const int P = 131;

typedef unsigned long long LL;
string s;
int m, l1, r1, l2, r2;
LL f[1000010];
// 手写快速幂
LL myPow(LL a, LL b) {
    LL ans = 1;
    while (b) {
        if (b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}
LL getHash(int l, int r) {
    return f[r] - f[l - 1] * myPow(P, r - l + 1);
}
int main() {
    cin >> s >> m;
    for (int i = 1; i <= s.length(); i++) {
        f[i] = f[i - 1] * P + (s[i - 1] - 'a' + 1);
    }
    for (int i = 0; i < m; i++) {
        cin >> l1 >> r1 >> l2 >> r2;
        if (getHash(l1, r1) == getHash(l2, r2)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}