#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
LL P = 1e9 + 7;
LL qpow(LL a, LL b, LL p) {
    LL ans = 1ll % p;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return ans;
}
class Solution {
   public:
    int minNonZeroProduct(int p) {
        LL t = (1ll << (p - 1)) - 1;
        LL a = (1ll << p) - 1, b = a - 1;
        // cout << b << " " << t << endl;
        return (a % P) * qpow(b % P, t, P) % P;
    }
};
