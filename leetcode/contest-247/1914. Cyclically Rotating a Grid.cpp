#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        for (int l = 0; l < min(m, n) / 2; l++) {
            vector<vector<int>> tmp = grid;
            int v = m - 2 * l, h = n - 2 * l;
            int times = k % (2 * h + 2 * v - 4);
            for (int g = 0; g < times; g++) {
                // 上面
                int i = l;
                for (int j = l; j < n - l; j++) {
                    if (j == n - 1 - l) {
                        tmp[i][j] = grid[i + 1][j];
                    } else {
                        tmp[i][j] = grid[i][j + 1];
                    }
                }
                i = m - 1 - l;
                for (int j = l; j < n - l; j++) {
                    if (j == l) {
                        tmp[i][j] = grid[i - 1][j];
                    } else {
                        tmp[i][j] = grid[i][j - 1];
                    }
                }
                // 左面
                int j = l;
                for (int i = l; i < m - l; i++) {
                    if (i == l) {
                        tmp[i][j] = grid[i][j + 1];
                    } else {
                        tmp[i][j] = grid[i - 1][j];
                    }
                }
                j = n - 1 - l;
                for (int i = l; i < m - l; i++) {
                    if (i == m - 1 - l) {
                        tmp[i][j] = grid[i][j - 1];
                    } else {
                        tmp[i][j] = grid[i + 1][j];
                    }
                }
                i = l;
                for (int j = l; j < n - l; j++) {
                    grid[i][j] = tmp[i][j];
                }
                i = m - 1 - l;
                for (int j = l; j < n - l; j++) {
                    grid[i][j] = tmp[i][j];
                }
                j = l;
                for (int i = l; i < m - l; i++) {
                    grid[i][j] = tmp[i][j];
                }
                j = n - 1 - l;
                for (int i = l; i < m - l; i++) {
                    grid[i][j] = tmp[i][j];
                }
            }
        }
        return grid;
    }
};
