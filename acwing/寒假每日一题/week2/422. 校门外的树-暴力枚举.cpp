/*
整个马路
L = 500, [0, 500]
区域：
[150, 300]
[100, 200]
[470, 471]
并集：
[100, 300], [470, 471]
移走个数：
201 + 2 = 203
剩余个数：
501 - 203 = 298

暴力：
对于每一个点枚举是否在某个区间内，如果在，那么就被移走了
时间复杂度：O(LM)
*/
#include <iostream>
using namespace std;
const int M = 110;

int l, m, s[M], t[M];
int main() {
    cin >> l >> m;
    for (int i = 0; i < m; i++) {
        cin >> s[i] >> t[i];
    }
    int ans = 0;
    for (int i = 0; i <= l; i++) {
        bool rm = false;
        for (int j = 0; j < m; j++) {
            if (i >= s[j] && i <= t[j]) {
                rm = true;
                break;
            }
        }
        if (!rm) ans++;
    }
    cout << ans << endl;
    return 0;
}