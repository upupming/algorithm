/*
Lucas 定理
c[n][m] = (c[n % p][m mod p] * c[n/p][m/p]) % p
当 n 和 m 都 < p 的时候用前一题的解法即可
时间复杂度：O(log_p N * p * log p)
*/
#include <iostream>
using namespace std;
typedef long long LL;

int qpow(int a, int b, int p) {
    int ans = 1 % p;
    while (b) {
        if (b & 1) {
            ans = 1ll * ans * a % p;
        }
        b >>= 1;
        a = 1ll * a * a % p;
    }
    return ans;
}

int C(int a, int b, int p) {
    if (b > a) return 0;
    LL ans = 1;
    // 上面下面都有 b 项，上面从 a 开始减小，下面从 1 开始增加
    for (int i = 1, j = a; i <= b; i++, j--) {
        ans = ans * j % p;
        ans = ans * qpow(i, p - 2, p) % p;
    }
    return ans;
}

int lucas(LL a, LL b, int p) {
    if (a < p && b < p) return C(a, b, p);
    return (LL)C(a % p, b % p, p) * lucas(a / p, b / p, p) % p;
}

int n, p;
LL a, b;
int main() {
    cin >> n;
    while (n--) {
        cin >> a >> b >> p;
        cout << lucas(a, b, p) << endl;
    }
    return 0;
}
