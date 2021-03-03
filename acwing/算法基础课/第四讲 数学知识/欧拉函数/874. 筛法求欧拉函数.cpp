#include <iostream>
using namespace std;
const int N = 1e6 + 10;

int primes[N], cnt, phi[N];
bool st[N];

void get_eulers(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            primes[cnt++] = i;
            // 质数 p 的欧拉函数就是 p - 1，因为 1, ..., (p-1) 都和 p 互质
            phi[i] = i - 1;
        }
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;
            // j 是 i 的最小质因子
            if (i % primes[j] == 0) {
                // (1 - 1/primes[j]) 在 phi[i] 中已经算过了，只需要将 i 变成 i * primes[j]
                phi[primes[j] * i] = phi[i] * primes[j];
                break;
            } else {
                // j 不是 i 的质因子
                // (1 - 1/primes[j]) 在 phi[i] 没有算过，除了将 i 变成 i * primes[j]，还需要乘上 (1 - 1/primes[j])，因此需要乘上 (primes[j] - 1)
                phi[primes[j] * i] = phi[i] * (primes[j] - 1);
            }
        }
    }
}

int n;

int main() {
    cin >> n;
    get_eulers(n);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += phi[i];
    }
    cout << ans << endl;
    return 0;
}
