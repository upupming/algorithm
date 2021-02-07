#include <bits/stdc++.h>
using namespace std;

/*
f[i][j] 表示从前 i 个 events 中选择 j 个 events 的最大收益
f[i][j] = max(
    f[i-1][j]，不选第 i 个事件
    f[r][j-1]，选第 i 个事件，就只能从 0-r 中选 j-1 个事件了，r 保证不和第 i 个事件冲突的最大事件
)

（事件下标从 1 开始）
最终结果为 f[n][k]
*/

const int N = 1e6 + 10;
struct P {
    int start, end, value;
    // 按照结束时间从小到大排序
    bool operator<(const P& b) {
        return end < b.end;
    }
} p[N];

class Solution {
   public:
    int maxValue(vector<vector<int>>& events, int k) {
        int n = events.size();
        for (int i = 1; i <= n; i++) {
            p[i] = {events[i - 1][0], events[i - 1][1], events[i - 1][2]};
        }
        sort(p + 1, p + 1 + n);

        vector<vector<int>> f(n + 1, vector<int>(k + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k; j++) {
                // case 1: 从 1-(i-1) 中选 j 个事件
                f[i][j] = f[i - 1][j];
                // case 2: 从 1-(r)中选 j -1 个事件
                int l = 0, r = i - 1;
                while (l < r) {
                    int mid = l + r + 1 >> 1;
                    if (p[mid].end < p[i].start)
                        l = mid;
                    else
                        r = mid - 1;
                }
                f[i][j] = max(f[i][j], f[r][j - 1] + p[i].value);
            }
        }

        return f[n][k];
    }
};