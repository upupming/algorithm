/*
字符串哈希，跟《兔子与兔子差不多》，相当于把字符串哈希拓展到了二维情况
*/
#include <iostream>
#include <unordered_set>
using namespace std;
const int P = 131, N = 1010;

typedef unsigned long long ULL;

ULL f[N][N], p[N * N];
unordered_set<ULL> allHash;
ULL m, n, a, b, q;
char str[N];
ULL calc(ULL *f, int l, int r) {
    return f[r] - f[l - 1] * p[r - l + 1];
}
int main() {
    cin >> m >> n >> a >> b;

    p[0] = 1;
    for (int i = 1; i <= m * n; i++) {
        p[i] = p[i - 1] * P;
    }
    // 避免 f[i][j] 转移时处理边界问题，下标从 1 开始
    for (int i = 1; i <= m; i++) {
        scanf("%s", str + 1);
        for (int j = 1; j <= n; j++) {
            f[i][j] = f[i][j - 1] * P + str[j] - '0';
        }
    }
    for (int j = b; j <= n; j++) {
        ULL hash = 0;
        int l = j - b + 1, r = j;
        for (int i = 1; i <= m; i++) {
            // calc 计算的是 [l, r] 共 b 列的 hash 值
            hash = hash * p[b] + calc(f[i], l, r);
            // 删掉不在窗口高位，相当于只保留 [i-a+1, i] 这些行
            if (i >= a + 1) hash -= calc(f[i - a], l, r) * p[a * b];
            if (i >= a) allHash.insert(hash);
        }
    }

    cin >> q;
    while (q--) {
        ULL hash = 0;
        for (int i = 1; i <= a; i++) {
            scanf("%s", str + 1);
            for (int j = 1; j <= b; j++) {
                hash = hash * P + str[j] - '0';
            }
        }

        // cout << hash << endl;
        if (allHash.count(hash))
            cout << 1 << endl;
        else
            cout << 0 << endl;
    }
    return 0;
}