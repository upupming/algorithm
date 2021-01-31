/*
1. 最优解中，所有高度都在 [0, 100] 之间（否则，总可以构造更优解，超出的点正好放在0和100这个边界点上）

枚举所有可能的区间：
[0, 17]
...
[83, 100]

对每个山峰进行分析，看分到哪个最合适
*/
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1100, D = 17;

int n, ans = 1e8, a[N];
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i + D <= 100; i++) {
        int cost = 0, l = i, r = i + D;
        for (int j = 0; j < n; j++) {
            if (a[j] < l)
                cost += (l - a[j]) * (l - a[j]);
            else if (a[j] > r)
                cost += (r - a[j]) * (r - a[j]);
        }
        ans = min(ans, cost);
    }
    cout << ans << endl;
    return 0;
}