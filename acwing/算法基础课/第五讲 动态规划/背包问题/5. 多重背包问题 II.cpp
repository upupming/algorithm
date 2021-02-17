/*
由于多重背包有限制，无法
f[i][j]   = max(f[i-1][j],
                f[i-1][j-v]+w,
                f[i-1][j-2v]+2w,
                ...,
                f[i-1][j-sv]+sw)
f[i][j-v] = max(f[i-1][j-v],
                f[i-1][j-2v]+w,
                f[i-1][j-3v]+2w,
                ...,
                f[i-1][j-sv]+(s-1)w,
                f[i-1][j-(s+1)v]+sw)
因为结尾多了一项，所以无法像完全背包那么优化

采用二进制的优化方式，将 s 分成若干块，分别有 1, 2, 4, ..., 2^{k-1}, c(多余部分) 件，最后直接运行 01 背包即可
*/
#include <iostream>
using namespace std;
// 12 = log(2000)
const int N = 1010 * 12, M = 2010;

int n, m, v[N], w[N];
int f[M], tot;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int a, b, s;
        cin >> a >> b >> s;
        int k = 1;
        while (k <= s) {
            v[++tot] = a * k;
            w[tot] = b * k;
            s -= k;
            k *= 2;
        }
        if (s > 0) {
            v[++tot] = a * s;
            w[tot] = b * s;
        }
    }
    for (int i = 1; i <= tot; i++) {
        for (int j = m; j >= v[i]; j--) {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    cout << f[m] << endl;
    return 0;
}
