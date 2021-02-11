#include <iostream>
using namespace std;
const int MOD = 1e4 + 7;

int qpow(int a, int b, int p = MOD) {
    int ans = 1 % p;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return ans;
}
int a, b, k, n, m;
int main() {
    cin >> a >> b >> k >> n >> m;
    // 要求的是 C_{k}^{n} a^n b^m
    // 先算 a^n 和 b^m
    int ans = qpow(a, n) * qpow(b, m) % MOD;
    // 接着算 C_{k}^{n}
    // 一共有 n 项
    for (int i = 1, j = k; i <= n; i++, j--) {
        // j / i，也就是 j * (i^{mod - 2})（乘法逆元）
        ans = ans * j % MOD;
        ans = ans * qpow(i, MOD - 2) % MOD;
    }
    cout << ans << endl;
    return 0;
}