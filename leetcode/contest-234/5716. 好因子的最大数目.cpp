#include <bits/stdc++.h>
using namespace std;
const int P = 1e9 + 7;

int qpow(int a, int b, int p = P) {
    int ans = 1 % p;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return ans;
}

class Solution {
   public:
    int maxNiceDivisors(int p) {
        if (p == 1) return 1;
        if (p == 2) return 2;
        int q = p / 3, r = p % 3;
        if (r == 0)
            return qpow(3, q);
        else if (r == 1)
            return qpow(3, q - 1) * 4ll % P;
        else
            return qpow(3, q) * 2ll % P;
    }
};
