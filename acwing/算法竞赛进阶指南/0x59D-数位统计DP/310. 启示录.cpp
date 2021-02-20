/*
f[i][j] 表示一共有 i 位，开头已经有 j 个 6 的非魔鬼数有多少个
*/
#include <iostream>
using namespace std;
const int N = 21;

long long f[N][4];
int t, n, m;

void init() {
    f[0][0] = 1;
    // // 初始化只有 1 位的情况，枚举 0~9 即可
    for (int k = 0; k <= 9; k++) f[1][k == 6]++;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            f[i + 1][j + 1] += f[i][j];
            f[i + 1][0] += f[i][j] * 9;
        }
        f[i + 1][3] += f[i][3] * 10;
    }
}

int main() {
    init();
    cin >> t;
    while (t--) {
        cin >> n;
        // 第 n 个魔鬼数有 m 位
        for (m = 3; f[m][3] < n; m++)
            ;
        // 试填第 i 位，末尾已有 k 个 6（k=3 也表示已经是魔鬼数）
        for (int i = m, k = 0; i; i--) {
            // 从小到大枚举第 i 位填的数字 j
            for (int j = 0; j <= 9; j++) {
                // 求出后边的 i-1 位有多少种填法能让整个数是魔鬼数
                long long cnt = f[i - 1][3];
                if (j == 6 || k == 3) {
                    for (int l = max(3 - k - (j == 6), 0); l < 3; l++) {
                        cnt += f[i - 1][l];
                    }
                }
                // 如果 cnt 比 n 小，说明第 n 个魔鬼数的第 i 位应该比 j 更大
                if (cnt < n) {
                    n -= cnt;
                } else {
                    // 否则，第 i 为就应该是 j
                    if (k < 3) {
                        if (j == 6)
                            k++;
                        else
                            k = 0;
                    }
                    cout << j;
                    break;
                }
            }
        }
        cout << endl;
    }
    return 0;
}
