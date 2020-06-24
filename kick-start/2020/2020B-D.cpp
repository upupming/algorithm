#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

int t, w, h, l, u, r, d;
const int max_n = 200005;
double log_2_factorial[max_n], last_h[max_n], last_w[max_n];

double cal(int n, int k) {
    return pow(2, log_2_factorial[n] - log_2_factorial[k] - log_2_factorial[n - k] - n);
}

double solve() {
    double ans = 0;

    // 计算边界情况的概率
    // (1. h)
    last_h[1] = 0.5 * cal(h - 1 + 1 - 2, 0);
    // (2, h) 到 (w, h)
    for (int i = 2; i <= w; i++) {
        last_h[i] = last_h[i - 1] + 0.5 * cal(h - 1 + i - 2, i - 1);
    }
    // (w, 1)
    last_w[1] = 0.5 * cal(w - 1 + 1 - 2, 0);
    // (w, 2) 到 (w, h)
    for (int i = 2; i <= h; i++) {
        last_w[i] = last_w[i - 1] + 0.5 * cal(w - 1 + i - 2, i - 1);
    }

    int left_sum = l - 1 + d + 1, right_sum = r + 1 + u - 1;
    // 左下角
    for (int i = l - 1, j = d + 1; i >= 1 && j <= h; i--, j++) {
        if (j == h) {
            ans += last_h[i];
        } else
            // 总共需要 left_sum - 2 步，i - 1 步向右
            ans += cal(left_sum - 2, i - 1);
    }
    // 右上角
    for (int i = r + 1, j = u - 1; i <= w && j >= 1; i++, j--) {
        if (i == w) {
            ans += last_w[j];
        } else
            ans += cal(right_sum - 2, i - 1);
    }

    return ans;
}

int main() {
    cin >> t;

    log_2_factorial[0] = 0;
    for (int i = 1; i < max_n; i++) {
        log_2_factorial[i] = log_2_factorial[i - 1] + log2(i);
    }

    for (int i = 1; i <= t; i++) {
        cin >> w >> h >> l >> u >> r >> d;
        printf("Case #%d: %lf\n", i, solve());
    }
    return 0;
}