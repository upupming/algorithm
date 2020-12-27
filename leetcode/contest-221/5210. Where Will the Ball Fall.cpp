#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<int> findBall(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> ans(n);
        typedef pair<int, int> PII;
        for (int j = 0; j < n; j++) {
            int r = 0, c = j;
            while (true) {
                int x, y;
                int action = grid[r][c];
                // 右下
                if (grid[r][c] == 1) {
                    // 特判
                    if (c + 1 < n && grid[r][c + 1] == -1) {
                        ans[j] = -1;
                        break;
                    } else {
                        x = r + 1, y = c + 1;
                    }
                } else {
                    if (c - 1 >= 0 && grid[r][c - 1] == 1) {
                        ans[j] = -1;
                        break;
                    } else {
                        x = r + 1, y = c - 1;
                    }
                }
                // 如果碰壁
                if (y == -1 || y == n) {
                    ans[j] = -1;
                    break;
                } else if (x == m) {
                    ans[j] = y;
                    break;
                } else {
                    r = x, c = y;
                }
            }
        }
        return ans;
    }
};