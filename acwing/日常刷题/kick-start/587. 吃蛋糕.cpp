/*
这是我想的错误的解法：
输入为 n 的话，可以吃的最大蛋糕为 x = sqrt(n) 下取整，吃的个数为 cnt = n/(x^2)，剩余 n - cnt * (x^2)，继续求解即可
错误的例子：
n = 41，求出来需要边长和个数为：
6 1
2 1
1 1
答案为 3
实际上最优解的边长和个数为：
5 1
4 1
答案为 2
因此这道题只能用完全背包求解
背包容量为 n，每种物品的体积为 x^2，价值为 1
f[i][j] 表示前 i 个物品，背包容量 j 下的最小价值
跟普通的完全背包不一样，这里求最小价值，只需要在初始化上稍加修改
*/
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e4 + 10;

int t, n, f[N];

int solve() {
    // 价值初始化为无穷大
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    int m = sqrt(n);
    for (int i = 1; i <= m; i++) {
        int vi = i * i, wi = 1;
        for (int j = vi; j <= n; j++) {
            f[j] = min(f[j], f[j - vi] + wi);
        }
    }
    return f[n];
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
