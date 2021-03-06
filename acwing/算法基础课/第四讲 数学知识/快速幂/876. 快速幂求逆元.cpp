/*
费马小定理：a^{p-1} = 1 mod p
因此 a 的逆元就是 a^{p-2}

只有当 a 是 p 的倍数的时候，a^? % p == 0，不存在逆元
*/
#include <iostream>
using namespace std;

int n, a, p;
int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % p;
        b >>= 1;
        a = 1ll * a * a % p;
    }
    return ans;
}
int main() {
    cin >> n;
    while (n--) {
        cin >> a >> p;
        if (a % p == 0)
            cout << "impossible" << endl;
        else
            cout << qpow(a, p - 2, p) << endl;
    }
    return 0;
}
