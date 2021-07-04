#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int P = 1e9 + 7;
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
    int countGoodNumbers(long long n) {
        LL e = (n + 1) / 2, o = n / 2;
        LL ans = 1;
        return 1ll * qpow(5, e, P) * qpow(4, o, P) % P;
    }
};
