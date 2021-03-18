/*
如果没有 wrapping 条件的话，直接选中位数作为最终目标即可，类似货仓选址
带上 wrapping 条件的话，相当于是一个环形的货仓选址问题了
想象成这 w 个数组成一个环，枚举最优方案所有可能的断开方法，然后再求中位数对应的距离差之和最小值即可

2 3 8 9 2+n 3+n 8+n 9+n
滑动窗口求中位数，关键是要 O(1) 时间算出区间内的总距离
[x0, ..., xt]，中位数 x[t/2]
[x1, ..., x{t+1}]，中位数 x[(t+2)/2] = x[t/2+1]
减少的距离：
- A. x0 被抛弃了：dist(x0, x[t/2])
- B. 右侧的点都减小了：dist(x[t/2], x[t/2]+1) * cnt
    - w 为偶数，cnt = w/2；w 为奇数 cnt = w/2
增加的距离：
- C. x{t+1} 被加上了：dist(x{t+1}, x[t/2+1])
- D. 左侧的点都增加了：dist(x[t/2], x[t/2]+1) * cnt
    - w 为偶数，cnt = w/2 - 1；w 为奇数 cnt = (w+1)/2 - 1；可以统一为 (w-1)/2
用 w = 4, n = 10 来举例子：
t = 3, x[t/2] = x[1], x[t/2+1] = x[2]
第一次的距离和 = 1 + 0 + 5 + 6 = 12
A = 1
B = 10
C = 4
D = 5
-(A + B) + C + D = -2
第二次的距离和 = 5 + 0 + 1 + 4 = 10
恰好满足 12+(-2)=10
*/
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;
const int W = 1e5 + 10;

int t, w, n;
LL x[2 * W];

LL solve() {
    LL ans = 1e18, pre, cur;
    for (int l = 0; l < w; l++) {
        int r = l + w;
        int mid = (l + r - 1) >> 1;
        if (l == 0) {
            cur = 0;
            for (int i = l; i < r; i++) {
                cur += abs(x[i] - x[mid]);
            }
            ans = min(ans, cur);
            pre = cur;
        } else {
            LL a = abs(x[l - 1] - x[mid - 1]);
            LL b = w / 2 * abs(x[mid - 1] - x[mid]);
            LL c = abs(x[r - 1] - x[mid]);
            LL d = (w - 1) / 2 * abs(x[mid - 1] - x[mid]);

            cur = pre - a - b + c + d;
            ans = min(ans, cur);
            pre = cur;
        }
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> w >> n;
        for (int i = 0; i < w; i++) {
            cin >> x[i];
            x[i + w] = x[i] + n;
        }
        sort(x, x + 2 * w);

        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
