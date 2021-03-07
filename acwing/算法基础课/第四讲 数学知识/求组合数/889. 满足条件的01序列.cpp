/*
按照卡特兰数的公式计算即可
*/
#include <iostream>
using namespace std;
const int N = 2e5 + 10, P = 1e9 + 7;

int qpow(int a, int b, int p) {
    int ans = 1 % p;
    while (b) {
        if (b & 1)
            ans = 1ll * ans * a % p;
        b >>= 1;
        a = 1ll * a * a % p;
    }
    return ans;
}

long long fact[N], infact[N];

void init() {
    fact[0] = infact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % P;
        infact[i] = infact[i - 1] * qpow(i, P - 2, P) % P;
    }
}

int C(int a, int b) {
    return (fact[a] * infact[b] % P) * infact[a - b] % P;
}

int main() {
    int n;
    cin >> n;
    init();
    cout << 1ll * C(2 * n, n) * qpow(n + 1, P - 2, P) % P << endl;
    return 0;
}
