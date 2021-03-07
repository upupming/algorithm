/*
枚举容斥定理右侧的每一项，时间复杂度为 2^20
*/
#include <iostream>
using namespace std;
typedef long long LL;
const int N = 20;

int n, m, p[N];
int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) cin >> p[i];

    int ans = 0;
    // 用位运算来记录每一个集合选或者不选
    for (int i = 1; i < 1 << m; i++) {
        // t 表示所有质数的乘积，cnt 表示当前集合的数量（用来确定正负号）
        int t = 1, cnt = 0;
        for (int j = 0; j < m; j++) {
            // 如果第 j 个集合选中的话
            if (i >> j & 1) {
                if ((LL)t * p[j] > n) {
                    t = -1;
                    break;
                }
                t *= p[j];
                cnt++;
            }
        }
        if (t == -1) continue;
        // 偶数个，负号
        if (cnt % 2 == 0) {
            ans -= n / t;
        } else {
            ans += n / t;
        }
    }
    cout << ans << endl;
    return 0;
}
