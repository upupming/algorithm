#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;
const int N = 65;

int t, x;
double w, e;
char ch[N][N][N];
void solve() {
    // dp[i][r][s], p=i-r-s
    double dp[N][N][N] = {-1};
    // 第 1 轮出 r/s/p，平均得分都是 (w+e+0)/3
    dp[1][1][0] = dp[1][0][1] = dp[1][0][0] = (w + e) / 3;
    ch[1][1][0] = 'r', ch[1][0][1] = 's', ch[1][0][0] = 'p';
    for (int i = 1; i <= 60; i++) {
        for (int r = 0; r <= i; r++) {
            for (int s = 0; s + r <= i; s++) {
                int p = i - r - s;
                // 下一轮对手出 3 种牌的概率
                double pP = (double)r / i, pR = (double)s / i, pS = (double)p / i;
                // 下一轮我们分别出 r, s, p 的得分
                double rScore = pS * w + pR * e, sScore = pP * w + pS * e, pScore = pR * w + pP * e;

                if (dp[i + 1][r + 1][s] < dp[i][r][s] + rScore) {
                    ch[i + 1][r + 1][s] = 'r';
                    dp[i + 1][r + 1][s] = dp[i][r][s] + rScore;
                }
                if (dp[i + 1][r][s + 1] < dp[i][r][s] + sScore) {
                    ch[i + 1][r][s + 1] = 's';
                    dp[i + 1][r][s + 1] = dp[i][r][s] + sScore;
                }
                if (dp[i + 1][r][s] < dp[i][r][s] + pScore) {
                    ch[i + 1][r][s] = 'p';
                    dp[i + 1][r][s] = dp[i][r][s] + pScore;
                }
            }
        }
    }

    int ci = 60, cr, cs;
    double best = -1;
    // 求 i==60 时的最大
    for (int r = 0; r <= 60; r++) {
        for (int s = 0; r + s <= 60; s++) {
            if (dp[60][r][s] > best) {
                cr = r, cs = s;
                best = dp[60][r][s];
            }
        }
    }
    string ans;
    while (ci >= 1) {
        switch (ch[ci][cr][cs]) {
            case 'r':
                ans += 'R';
                cr--;
                break;
            case 's':
                ans += 'S';
                cs--;
                break;
            case 'p':
                ans += 'P';
                break;
        }
        ci--;
    }
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
}
int main() {
    cin >> t >> x;
    for (int i = 1; i <= t; i++) {
        cin >> w >> e;
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
