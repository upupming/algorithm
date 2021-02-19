/*
f[i][j][k]: 一共有 i 位，最高位为 j 的数中 k 出现的次数（k 为 0~9）
枚举所有可能的次高位为 l，那么：
f[i][j][k] += f[i-1][l][k]
如果 k == j，还需要 f[i][j][k] += 10^{i-1}（因为一共有 10^{i-1} 个数，每个数最前面都是 j (== k)）
*/
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
const int N = 15;

int f[N][10][10];
void init() {
    // 初始化 1 位的情况
    for (int j = 0; j <= 9; j++) f[1][j][j] = 1;
    for (int i = 2; i < N; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {
                if (k == j) f[i][j][k] += pow(10, i - 1);
                for (int l = 0; l <= 9; l++) {
                    f[i][j][k] += f[i - 1][l][k];
                }
            }
        }
    }
}
int dp(int n, int k) {
    // n == 0 只有 1 个 0 存在
    if (n == 0) return k == 0;
    vector<int> a;
    while (n) a.push_back(n % 10), n /= 10;
    int len = a.size(), ans = 0, last = 0;
    for (int i = len - 1; i >= 0; i--) {
        int t = a[i];
        // 枚举左侧 < t 分支，本题不算前导 0，所以左边第一个分支取值为 1~(a_i-1)
        for (int x = (i == len - 1); x < t; x++) {
            ans += f[i + 1][x][k];
        }
        // 前面每一个 k 都会被统计 pow(10, i) 次，总共有 last 个 k
        ans += last * t * pow(10, i);
        // 枚举右侧 == t 分支，算上前面的 k 的个数
        // 无需做任何操作
        // 记录 last
        if (t == k) last++;

        // 最右侧
        if (i == 0) ans += last;
    }
    //所有0~n-1位数的方案数量,例如000123是不合法的,而123确实合法的
    for (int i = 1; i < a.size(); i++)
        for (int j = i != 1; j <= 9; j++)
            ans += f[i][j][k];
    return ans;
}
int a, b;
int main() {
    init();
    while (cin >> a >> b, a, b) {
        if (a > b) swap(a, b);
        for (int k = 0; k <= 9; k++) {
            cout << (dp(b, k) - dp(a - 1, k)) << " ";
        }
        cout << endl;
    }
    return 0;
}
