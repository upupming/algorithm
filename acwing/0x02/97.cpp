#include <cmath>
#include <iostream>
#include <map>
using namespace std;

long long a, b;
map<long long, long long> factor;
const long long MOD = 9901;

long long powWithMod(int p, int c) {
    p = p % MOD;
    long long ans = 1;
    for (; c > 0; c >>= 1) {
        if (c & 1) ans = ans * p % MOD;
        p = p * p % MOD;
    }
    return ans;
}

long long sum(long long p, long long c) {
    if (p == 0) return 0;
    if (c == 0) return 1;
    // if (c == 1) return p + 1;
    long long ans;
    // c 是奇数
    if (c % 2) {
        ans = (((1 + powWithMod(p, c / 2 + 1)) % MOD) * sum(p, c / 2)) % MOD;
    } else {
        ans = ((((1 + powWithMod(p, c / 2)) % MOD) * sum(p, c / 2 - 1)) % MOD + powWithMod(p, c)) % MOD;
    }
    // cout << p << ", " << c << ", " << ans << endl;
    return ans;
}

int main() {
    cin >> a >> b;
    long long sqrt_a = sqrt(a);
    // 算出 a 的所有的质因数
    for (long long i = 2; i <= sqrt_a; i++) {
        while (a % i == 0) {
            a /= i;
            factor[i]++;
        }
    }
    if (a != 1) factor[a]++;
    long long ans = 1;
    for (auto f : factor) {
        ans = (ans * sum(f.first, f.second * b)) % MOD;
    }
    cout << ans << endl;
    return 0;
}