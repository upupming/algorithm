#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
class Solution {
   public:
    vector<vector<int>> highestPeak(vector<vector<int>>& w) {
        int m = w.size(), n = w[0].size();
        vector<vector<int>> h(m, vector<int>(n, INT_MAX));
        vector<vector<bool>> v(m, vector<bool>(n, false));
        queue<PII> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (w[i][j]) {
                    h[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        while (q.size()) {
            auto t = q.front();
            q.pop();
            for (int k = 0; k < 4; k++) {
                int x = t.first + dx[k];
                int y = t.second + dy[k];
                if (x < 0 || x >= m || y < 0 || y >= n) continue;
                if (v[x][y]) continue;
                v[x][y] = true;
                h[x][y] = min(h[x][y], h[t.first][t.second] + 1);
                q.push({x, y});
            }
        }
        return h;
    }
};
