#include <climits>
#include <iostream>
using namespace std;

/*
二分：
自变量 x: 平均值，范围是 [arr_min, arr_max]
值域：0 (至少包含 F 块地的平均值无法 >= x，invalid), 1 (至少包含 F 块地的平均值可以 >= x，valid)
值域的单调性：假设最优的 x* 是 S（存在序列 a_i, ...a_j 满足 avg(a[i..j]) >= S 且 (j - i) >= F，且类似形式不存在 > S 的 x），那么 x <= S，一定都是 valid 的（平均数 >= S >= x），因为 x 在 [arr_min, arr_max] 之间，这样的序列拓展一定是存在的）；对于 x > S，肯定是 invalid，否则就有更优的解了。

因此我们可以使用二分的方法解决这个问题。
注意本题是实数域上的二分，要求的精度是 10^3，所以 eps = 10^-5 就可以了。


*/

int n, f, a[100010], a_min, a_max;
double eps = 1e-5, sum[100010];

// 平均值 x 能否达到
// max_{i-j>=F}{A_{j+1} + ... + A_{i}}
//  = max_{F<=i<=n}{sum_i - min_{0<=j<=i-F}{sum_j}}
// O(n)
bool valid(double x) {
    // 现将整个数组减去 x，转化成判定：
    // 是否存在一个长度不小于 F 的子段，子段和非负
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + (a[i] - x);
    }
    double ans = -1e10;
    // min{sum_j} 中最小的值，每次只会增加一个值，就是 sum_{i-F}
    double minVal = 1e10;
    for (int i = f; i <= n; i++) {
        minVal = min(minVal, sum[i - f]);
        ans = max(sum[i] - minVal, ans);
    }
    return ans >= 0;
}

int main() {
    cin >> n >> f;
    a_min = INT_MAX, a_max = INT_MIN;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a_min = min(a_min, a[i]), a_max = max(a_max, a[i]);
    }
    double l = a_min, r = a_max;
    // O(n log (r-l))
    while (abs(l - r) > eps) {
        double mid = (l + r) / 2;
        if (valid(mid))
            l = mid;
        else
            r = mid;
    }
    // l: 6499, r: 6500
    // 为什么只能用 r 而不能用 l 呢？
    // 因为已经认为 l、r 都是 valid 的了，就返回一个大一点的就行了
    // 题目要求的就是最大，用 l 向下取整答案会小 1
    cout << (int)(r * 1000) << endl;
    return 0;
}