/*
f[i][j] 表示前 i 个数，总和为 j 的方案总数
每个数可以选任意多次，属于完全背包
*/
#include <iostream>
using namespace std;
const int N = 4010;

int n;
long long f[N], P = 2147483648;
int main() {
    cin >> n;
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            f[j] = (f[j] + f[j - i]) % P;
        }
    }
    cout << f[n] - 1 << endl;
    return 0;
}
