/*
f[i][j][k]: 一共有 i 位，且最高位数字是 j，且所有位数字和模 N 结果为 k 的数的个数
枚举次高位可能填的所有 x
f[i][j][k] += f[i-1][x][(k-j) % N]
*/
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 15, M = 110;

int p, f[N][10][M];
// 避免出现取模的结果得到负数
int mod(int x, int y) {
    return (x % y + y) % y;
}
void init() {
    memset(f, 0, sizeof f);
    for (int i = 0; i <= 9; i++) f[1][i][i % p] = 1;
    for (int i = 2; i < N; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k < p; k++) {
                // 枚举最高位填 x
                for (int x = 0; x <= 9; x++) {
                    f[i][j][k] += f[i - 1][x][mod(k - j, p)];
                }
            }
        }
    }
}
int dp(int n) {
    if (n == 0) return 1;
    int ans = 0, last = 0;
    vector<int> num;
    while (n) num.push_back(n % 10), n /= 10;
    int len = num.size() - 1;
    for (int i = len; i >= 0; i--) {
        int x = num[i];
        // 左侧分支：第 i 位放 0~(x-1)
        for (int j = 0; j < x; j++) {
            ans += f[i + 1][j][mod(-last, p)];
        }
        // 右侧分支，直接填 x
        last += x;
        // 最右侧叶子节点
        if (i == 0 && last % p == 0) ans++;
    }
    return ans;
}
int l, r;
int main() {
    while (cin >> l >> r >> p) {
        init();
        cout << dp(r) - dp(l - 1) << endl;
    }
    return 0;
}
