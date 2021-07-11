#include <bits/stdc++.h>
using namespace std;
/*
时间 <= maxTime 的最小费用路径
二维最短路问题，需要拆点，将一个点拆分为权重个点
d[i][j] 表示: 花 j 单位时间走到第 i 个点的情况下的最小费用路径的费用是多少
10^6 个点做 SPFA、Dijkstra
a -> b，可以用 d[a][j] 更新点 d[b][j+c], c 是边权大小
*/

const int N = 1010, M = 2010, INF = 0x3f3f3f3f;

int head[N], ver[M], edge[M], Next[M], tot;
void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z;
    Next[tot] = head[x], head[x] = tot;
}
// d[i][j] 表示: 花 j 单位时间走到第 i 个点的情况下的最小费用路径的费用是多少
int d[N][N], v[N][N];
typedef pair<int, int> PII;
class Solution {
   public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size();
        memset(head, 0, sizeof head), tot = 0;
        for (auto& e : edges) {
            int a = e[0], b = e[1], c = e[2];
            add(a, b, c), add(b, a, c);
        }
        memset(d, 0x3f, sizeof d);
        d[0][0] = passingFees[0], v[0][0] = 1;
        queue<PII> q;
        q.push({0, 0});

        while (q.size()) {
            auto t = q.front();
            q.pop();
            v[t.first][t.second] = false;

            for (int i = head[t.first]; i; i = Next[i]) {
                // t.first -> x, 边权为 edge[i]
                int x = ver[i], y = t.second + edge[i];
                // 时间超出，不用考虑
                if (y > maxTime) continue;
                if (d[x][y] > d[t.first][t.second] + passingFees[x]) {
                    d[x][y] = d[t.first][t.second] + passingFees[x];
                    if (!v[x][y]) {
                        q.push({x, y});
                        v[x][y] = 1;
                    }
                }
            }
        }

        int ans = INF;
        for (int i = 0; i <= maxTime; i++) {
            ans = min(ans, d[n - 1][i]);
        }
        if (ans == INF) ans = -1;
        return ans;
    }
};
