/*
求一下每个数能够到达右边最远的什么的地方，这一步时间复杂度为 O(RC^2)
枚举每一列作为底边，高就是到右边的长度，题目就转化为了「直方图中的最大矩形」
时间复杂度 O(RC)
*/
#include <iostream>
using namespace std;
const int N = 310;

int t, r, c, k, v[N][N], d[N][N], h[N], s[N], l[N], rht[N];

int get(int h[]) {
    h[0] = h[r+1] = -1;
    int tt = 0;
    s[0] = 0;
    for (int i = 1; i <= r; i++) {
        while (h[s[tt]] >= h[i]) tt--;
        l[i] = s[tt];
        s[++tt] = i;
    }
    tt = 0;
    s[0] = r + 1;
    for (int i = r; i >= 1; i--) {
        while (h[s[tt]] >= h[i]) tt--;
        rht[i] = s[tt];
        s[++tt] = i;
    }
    int ans = 0;
    for (int i = 1; i <= r; i++) {
        int width = i - l[i] + rht[i] - i - 1;
        ans = max(ans, width * h[i]);
    }
    return ans;
}
int solve() {
    // 求每一个点最远能够到达右边的什么地方
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            d[i][j] = j;
            int m0 = v[i][j], m1 = v[i][j];
            for (int l = j+1; l <= c; l++) {
                m0 = max(m0, v[i][l]);
                m1 = min(m1, v[i][l]);
                if (m0 - m1 <= k) d[i][j] = l;
                else break;
            }
        }
    }
    int ans = 0;
    // 对每一列，运行直方图中的最大矩形
    for (int j = 1; j <= c; j++) {
        for (int i = 1; i <= r; i++) {
            h[i] = d[i][j] - j + 1;
        }
        ans = max(ans, get(h));
    }
    return ans;
}
int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> r >> c >> k;
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                cin >> v[i][j];
            }
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
