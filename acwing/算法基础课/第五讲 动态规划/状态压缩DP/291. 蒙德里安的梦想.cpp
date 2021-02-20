/*
f[i][j]: 表示第 i 列的第 j 个状态，j 状态位等于 1 表示上一列所有格子横放，本列有格子捅出来。
f[i][j] += f[i-1][k]
要求：
1. i 列和 i-1 列不同时捅出来
2. i 列和 i-1 列求或，不能有奇数个连续的 0
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 12, M = 1 << N;

int st[M], n, m;
long long f[N][M];
int main() {
    while (cin >> n >> m, n, m) {
        for (int i = 0; i < 1 << n; i++) {
            int cnt = 0;
            st[i] = true;
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) {
                    // i 存在奇数个连续的 0
                    if (cnt & 1) st[i] = false;
                    cnt = 0;
                } else
                    cnt++;
            }
            if (cnt & 1) st[i] = false;  // 扫完后要判断一下最后一段有多少个连续的0
        }
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        for (int i = 1; i <= m; i++) {
            for (int j = 0; j < 1 << n; j++) {
                for (int k = 0; k < 1 << n; k++) {
                    if ((j & k) == 0 && (st[j | k])) {
                        f[i][j] += f[i - 1][k];
                    }
                }
            }
        }
        cout << f[m][0] << endl;
    }
    return 0;
}
