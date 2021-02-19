/*
f[i][j] 表示一共有 i 位，且最高位为 j 的方案数（j 可能为 0）
*/
#include <iostream>
#include <vector>
using namespace std;
const int N = 15;

int f[N][N];

void init() {
    for (int j = 0; j <= 9; j++) f[1][j] = 1;
    for (int i = 2; i <= N; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {
                if (abs(k - j) >= 2) f[i][j] += f[i - 1][k];
            }
        }
    }
}
int dp(int n) {
    // 按照题意 0 不可能出现
    if (n == 0) return 0;

    // last 表示上一位是什么，因为最高位填什么都可以，只要初始化为与 0-9 相差均 >=2 的数即可
    int ans = 0, last = -10;
    vector<int> num;
    while (n) num.push_back(n % 10), n /= 10;
    for (int i = num.size() - 1; i >= 0; i--) {
        int x = num[i];
        // 左侧分支
        // 最高位只能从 1 开始填，其他可以从 0 开始填
        for (int j = (i == num.size() - 1); j < x; j++) {
            if (abs(j - last) >= 2) ans += f[i + 1][j];
        }
        // 右侧分支
        // 如果不能填 x，直接 break
        if (abs(x - last) < 2) break;
        // 如果能够填 x
        last = x;

        if (i == 0) ans++;
    }

    // 处理前导 0 的情况，有前导 0 的话，数的总位数可能是 1-num.size() - 1
    for (int i = 1; i <= num.size() - 1; i++) {
        // j 从 1 开始
        for (int j = 1; j <= 9; j++) {
            ans += f[i][j];
        }
    }
    return ans;
}
int l, r;
int main() {
    init();
    int l, r;
    cin >> l >> r;
    cout << dp(r) - dp(l - 1) << endl;
    return 0;
}
