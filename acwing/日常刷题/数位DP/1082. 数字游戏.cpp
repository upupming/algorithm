/*
数位 dp
f[i][j] 表示所有最高位是 j，且一共有 i 位不降数的集合
次高位只能填 j, j+1, ..., 9，填完 k 之后，变成了子集合 f[i-1][k]
*/
#include <iostream>
#include <vector>
using namespace std;
// 十进制表示下最多 10 位
const int N = 15;

int f[N][N];
// dp 过程
void init() {
    // 初始条件
    for (int i = 0; i <= 9; i++) f[1][i] = 1;
    // 状态计算
    for (int i = 2; i <= N; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = j; k <= 9; k++) {
                f[i][j] += f[i - 1][k];
            }
        }
    }
}
int dp(int n) {
    // n = 0，只有 0 这一种方案；0 一般都需要特判，因为下面 while 循环对 0 不会执行
    if (!n) return 1;
    vector<int> num;
    while (n) num.push_back(n % 10), n /= 10;

    int ans = 0;
    // 保存上一位的最大值，之后只能填 >= lt 的值，初始为 0
    int lt = 0;
    for (int i = num.size() - 1; i >= 0; i--) {
        int x = num[i];
        // 左边分支，因为要保持不降序，所以 j >= lt
        for (int j = lt; j < x; j++) {
            ans += f[i + 1][j];
        }
        // 如果上一位大于 x 的话，不构成降序，所以右边分支结束
        if (lt > x) break;
        // 走右边分支，填上 x
        lt = x;

        // 全部枚举完了也同样构成一种方案
        if (i == 0) ans++;
    }
    return ans;
}
int n, m;
int main() {
    init();
    while (cin >> n >> m) {
        cout << dp(m) - dp(n - 1) << endl;
    }
    return 0;
}
