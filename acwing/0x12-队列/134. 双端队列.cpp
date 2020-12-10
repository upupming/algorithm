/*
argsort 之后，下标数组每个波谷是一个 deque
存在相同数的时候，argsort 有多种选择，应该让波谷数尽量少

argsort 通常通过 pair 实现，first 存数据，second 存原始下标
*/
#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;

int n;
pair<int, int> s[200010];
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> s[i].first, s[i].second = i;
    sort(s, s + n);

    int ans = 0;
    // 第一个区间始终看做递减区间，dir 表示当前趋势是下降还是上升
    int last = INT_MAX, dir = -1;
    // 存一下具有相等数的区间的下标最大值和下标最小值
    int maxp, minp;
    for (int i = 0; i < n;) {
        maxp = minp = s[i].second;
        int j = i + 1;
        // 找到一段相等的数
        while (j < n && s[j].first == s[i].first) {
            maxp = max(maxp, s[j].second);
            minp = min(minp, s[j].second);
            j++;
        }

        // cout << i << " " << j << endl;
        // 看看这一段能不能继续下降
        if (dir == -1) {
            if (maxp <= last) {
                // 继续下降
                // cout << "case 1" << endl;
                last = minp;
            } else {
                // cout << "case 2" << endl;
                // 必须改为递增状态
                last = maxp;
                dir = 1;
                ans++;
            }
        } else {
            if (minp >= last) {
                // 继续上升
                // cout << "case 3" << endl;
                last = maxp;
            } else {
                // cout << "case 4" << endl;
                // 必须改为递减状态
                last = minp;
                dir = -1;
            }
        }
        i = j;
    }
    // 边界情况特殊考虑一下
    if (dir == -1) ans++;
    cout << ans << endl;

    return 0;
}