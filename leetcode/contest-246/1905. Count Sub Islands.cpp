#include <bits/stdc++.h>
using namespace std;
class Solution {
    vector<vector<int>> g1, g2;
    vector<vector<int>> c1, c2;
    int m, n, ans = 0;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool valid(int i, int j) {
        return i >= 0 && i < m && j >= 0 && j < n;
    }
    void dfs(int i, int j, int color) {
        if (c1[i][j] != -1) return;
        c1[i][j] = color;
        for (int k = 0; k < 4; k++) {
            int x = i + dx[k], y = j + dy[k];
            // cout << i << " " << j << " " << x << " " << y << endl;
            if (valid(x, y) && g1[x][y] == 1) {
                dfs(x, y, color);
            }
        }
    }
    bool dfs1(int i, int j, int color, int color1) {
        if (c2[i][j] != -1) {
            return 1;
        }
        if (c1[i][j] != color1) {
            return 0;
        }
        c2[i][j] = color;
        bool ok = 1;
        for (int k = 0; k < 4; k++) {
            int x = i + dx[k], y = j + dy[k];
            if (valid(x, y) && g2[x][y] == 1) {
                if (!dfs1(x, y, color, color1)) ok = false;
            }
        }
        return ok;
    }

   public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        g1 = grid1, g2 = grid2;
        m = g1.size(), n = g1[0].size();
        c1 = vector<vector<int>>(m, vector<int>(n, -1));
        c2 = vector<vector<int>>(m, vector<int>(n, -1));
        int color = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (c1[i][j] == -1 && g1[i][j] == 1) {
                    // cout << i << " " << j << " " << color << endl;
                    dfs(i, j, color++);
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (c2[i][j] == -1 && c1[i][j] != -1 && g2[i][j] == 1) {
                    ans += dfs1(i, j, color++, c1[i][j]);
                }
            }
        }
        return ans;
    }
};
