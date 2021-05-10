#include <cassert>
#include <cmath>
#include <iostream>
using namespace std;
typedef long long LL;

int t;
LL z;

bool is_prime(LL x) {
    if (x <= 1) return false;
    for (LL i = 2; i <= x / i; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

LL solve() {
    LL x = sqrt(z), a, b, c;

    LL t = x;
    for (; !is_prime(t); t--) {
        ;
    }
    b = t--;

    // Z = 6 时，特殊情况，不存在第二小的质因子 a
    if (t < 2) {
        a = z;
    } else {
        for (; !is_prime(t); t--) {
            ;
        }
        a = t;
    }

    t = x + 1;
    for (; !is_prime(t); t++) {
        ;
    }
    c = t;

    if (b * c <= z) return b * c;
    if (a * b <= z) return a * b;
    assert(false);
    return -1;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> z;
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
