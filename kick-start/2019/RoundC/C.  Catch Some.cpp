/*
动态规划，思想比较复杂，但是实现起来非常简单

1. 一旦观察完颜色 a 的狗，下次不会再穿颜色 a 的衣服继续观察颜色 a 的狗，否则总可以移到前面这一次来
2. 最后一种颜色的狗看完之后，不需要耗费返回到 home 的时间，这个有点特殊，可以先考虑最后一趟也要返回到 home 的情况
    颜色处理的顺序不影响，只要确定是哪些颜色，终止点坐标即可
    可以使用动态规划求解
    dp[i][j]: 观察 j 个狗，颜色 1-i 的观察与否情况已经确定
    最终答案 dp[C][K], C 表示颜色种数

    dp[i][j] = min(dp[i-1][j] + 0, dp[i-1][j-1] + 2 * Xi,1, dp[i-1][j-2] + 2 * Xi, 2, dp[i-1][j-3] + 2 * Xi, 3...)
    Xc, d represents the distance of the d-th dog of c-th color from Bundle's house.
    带有 j-k 的每一项表示从第 i 种颜色中选了 k 个狗，k>=0
    dp[i][?] 计算的时候，总的转移计算量为 O(N)，因为各种颜色的狗的总数之和为 N
    总的 dp 计算代价为 O(N^2)
3. 分别假定以任何颜色作为最后一个颜色，这种颜色的代价不需要乘以 2，只需要多一层循环即可

优化：
dp[i][j][k]: 其中 k 表示在前 i 种颜色中，是否已经确定过作为最后一个颜色的点了
转移方程：
dp[i][j][0] = min(dp[i-1][j][0] + 0, dp[i-1][j-1][0] + 2 * Xi,1, dp[i-1][j-2][0] + 2 * Xi, 2 ...)
dp[i][j][1] = min(min(dp[i-1][j][1] + 0, dp[i-1][j-1][1] + 2 * Xi,1, dp[i-1][j-2][1] + 2 * Xi, 2 ...),
min(dp[i-1][j][0] + 0, dp[i-1][j-1][0] + Xi,1, dp[i-1][j-2][0] + Xi, 2 ...))
*/
#include <algorithm>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
const int N = 1010;

int p[N], a[N], t, n, k, dp[N][N][2];
unordered_map<int, vector<int>> c2p;
int solve() {
    int m = c2p.size(), i = 1, cnt = 0;
    memset(dp, 0x3f, sizeof dp);
    dp[0][0][0] = dp[0][0][1] = 0;
    for (auto& [color, points] : c2p) {
        cnt += points.size();
        sort(points.begin(), points.end());
        for (int j = 0; j <= cnt; j++) {
            for (int k = 0; k <= j && k <= points.size(); k++) {
                dp[i][j][0] = min(
                    dp[i][j][0],
                    // 第 i 种颜色选 k 个点
                    dp[i - 1][j - k][0] + 2 * points[k - 1]);
                dp[i][j][1] = min(
                    min(
                        dp[i][j][1],
                        // 第 i 种颜色选 k 个点
                        dp[i - 1][j - k][1] + 2 * points[k - 1]),
                    // 第 i 种颜色选 k 个点，第 i 种颜色作为最后一轮
                    dp[i - 1][j - k][0] + points[k - 1]);
            }
        }
        i++;
    }
    return dp[m][k][1];
}
int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> k;
        c2p.clear();
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            c2p[a[i]].push_back(p[i]);
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
