class Solution {
    int X[4] = { 0, 0, -1, 1}, Y[4] = { 1, -1, 0, 0 };
    int m, n;
    bool check(int x, int y) {
        if (x < 0 || x >= m || y < 0 || y >= n) return false;
        return true;
    }
    bool dfs(int i, int j, vector<vector<int>>& grid, vector<vector<bool>>& vis) {
        bool ans = true;
        vis[i][j] = true;
        cout << i << ", " << j << endl;
        for (int ii = 0; ii < 4; ii++) {
            int x = i + X[ii], y = j + Y[ii];
            // out, not ok
            if (!check(x, y)) {
                ans = false;
            }
            else if (!vis[x][y]) {
                bool tmp =  grid[x][y] == 1 || dfs(x, y, grid, vis);
                ans = ans && tmp;
            }
        }
        return ans;
    }
public:
    int closedIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int ans = 0;
        
        vector<vector<bool>> vis(m, vector<bool>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 && !vis[i][j]) {
                    ans += dfs(i, j, grid, vis);
                }
                // for (int i = 0; i < m; i++) {
                //     for (int j = 0; j < n; j++) {
                //         cout << vis[i][j] << " ";
                //     }
                //     cout << endl << endl;
                // }
                // cout << endl;
            }
        }
        return ans;
    }
};