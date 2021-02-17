/*
f[i][j] 表示只从 1~i 中选，且总和为 j 的方案数
// 选 i 还是不选 i
f[i][j] = f[i-1][j] + f[i][j-i]（这里是 i，因此优化后的数组从前往后循环）


其他算法
状态表示：
f[i][j]表示总和为i，总个数为j的方案数

状态转移方程：
f[i][j] = f[i - 1][j - 1] + f[i - j][j];
- f[i - 1][j - 1]，加上一个数 1 即可，数的个数变为 i，总和变为 j
- f[i - j][j]，对每个数都 +1，就变成了一种新的方案，方案里面没有数 1
*/
#include <iostream>
using namespace std;
const int N = 1010, mod = 1e9 + 7;

int n, f[N];
int main() {
    cin >> n;
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            f[j] = (f[j] + f[j - i]) % mod;
        }
    }
    cout << f[n] << endl;
    return 0;
}
