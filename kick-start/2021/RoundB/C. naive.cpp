#include <iostream>
using namespace std;
typedef long long LL;
const LL N = 1e9 + 10;

int t, n, k;
string s;

LL primes[N], cnt, z;
bool st[N];
// 线性筛法
// 每个数只会被自己的最小质因子筛掉，时间复杂度为 O(n)
void get_primes_l(LL n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        // j < cnt 没有必要，因为 i 是合数的时候，枚举到最小质因子一定会 break
        // 如果 i 是质数 primes[j] == i 的时候也会停止循环
        for (int j = 0; primes[j] <= n / i; j++) {
            if (primes[j] * i < N)
                // primes[j] 是 primes[j] * i 的最小质因子
                st[primes[j] * i] = true;
            // primes[j] 一定是 i 的最小质因子（因为 y 是从小到大枚举的）
            if (i % primes[j] == 0) break;
        }
    }
}

bool valid(int mid) {
    if (primes[mid] * primes[mid + 1] <= z) return true;
    return false;
}

LL solve() {
    int l = 0, r = cnt - 2;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (valid(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return primes[l] * primes[l + 1];
}

int main() {
    cin >> t;
    get_primes_l(N);
    for (int i = 1; i <= t; i++) {
        cin >> z;
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
