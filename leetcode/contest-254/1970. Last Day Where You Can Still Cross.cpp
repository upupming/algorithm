#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    unordered_map<int, unordered_map<int, int>> mp;
    int row, col;
    unordered_map<int, unordered_map<int, int>> f;
    unordered_map<int, unordered_map<int, int>> v;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    bool dfs(int i, int j, int m) {
        if (f.count(i) && f[i].count(j)) {
            return f[i][j];
        }
        // 如果这个点变成蓝色了
        if (mp.count(i) && mp[i].count(j) && mp[i][j] < m) {
            return f[i][j] = false;
        }
        if (i == row - 1) {
            return f[i][j] = true;
        }
        v[i][j] = true;
        for (int k = 0; k < 4; k++) {
            int x = dx[k] + i, y = dy[k] + j;
            if (x >= 0 && x < row && y >= 0 && y < col) {
                // 不是直接用 v[x][y] 可以加快速度，否则 TLE
                if (!(v.count(x) && v[x].count(y) && v[x][y]) && dfs(x, y, m)) {
                    v[i][j] = false;
                    return f[i][j] = true;
                }
            }
        }
        v[i][j] = false;
        return f[i][j] = false;
    }
    bool valid(int m) {
        f.clear();
        v.clear();

        for (int j = 0; j < col; j++) {
            // cout << j << " " << m << endl;
            if (dfs(0, j, m)) return true;
        }
        return false;
    }
    int latestDayToCross(int _row, int _col, vector<vector<int>>& cells) {
        for (int i = 0; i < cells.size(); i++) {
            auto& c = cells[i];
            mp[c[0] - 1][c[1] - 1] = i;
        }
        row = _row, col = _col;
        int l = 0, r = row * col;
        // 找最大的 valid
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (valid(mid))
                l = mid;
            else
                r = mid - 1;
        }
        return l;
    }
};
