#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;

int t;
typedef long long LL;
LL n, p[N];
double f[2][N], g[N];

void solve() {
    cin >> n;
    printf("%.8f\n", (double)g[n] / p[n]);
}

int main() {
    cin >> t;
    p[1] = 1;
    for (int i = 2; i < N; i++) p[i] = i * p[i - 1];
    f[0][1] = 1, g[1] = 1;
    for (int i = 2; i < N; i++) {
        for (int k = 1; k < N; k++) {
            f[1][k] = (f[0][k - 1] + f[0][k] * (i - 1));
            // cout << i << " " << k << " " << f[1][k] << endl;
            g[i] += f[1][k] * k;
        }
        for (int k = 1; k < N; k++) {
            f[0][k] = f[1][k];
        }
    }
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
