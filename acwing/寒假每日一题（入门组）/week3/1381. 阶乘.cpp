/*
质因数分解的算数基本定理
N = \sigma p_i ^ c^_i
把 2 和 5 单独拎出来算即可，min (2, 5) 表示末尾的 0 的个数，多出的 2 或 5 需要乘上去
其余部分每次乘的时候都对 10 取一下模

时间复杂度 n log n
*/

#include <iostream>
using namespace std;
const int N = 1100;

int n, f[N];
int main() {
    cin >> n;
    int ans = 1, d2 = 0, d5 = 0;
    for (int i = 2, x; i <= n; i++) {
        x = i;
        while (x % 2 == 0) d2++, x /= 2;
        while (x % 5 == 0) d5++, x /= 5;
        ans = ans * x % 10;
    }
    int k = min(d2, d5);
    for (int i = 0; i < d2 - k; i++) ans = ans * 2 % 10;
    for (int i = 0; i < d5 - k; i++) ans = ans * 5 % 10;
    cout << ans << endl;
    return 0;
}