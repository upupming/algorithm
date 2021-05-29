#include <bits/stdc++.h>
using namespace std;
const int N = 420, OFFSET = 100;
// sum1[i+j][i+1], sum2[i-j][i+1]
int sum1[N][N], sum2[N][N];
class Solution {
   public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        memset(sum1, 0, sizeof sum1);
        memset(sum2, 0, sizeof sum2);

        for (int s = 0; s <= n + m - 2; s++) {
            for (int i = max(s - n + 1, 0); i < m; i++) {
                int j = s - i;  // j 越来越小
                if (j < 0) break;
                sum1[s][i + 1] = sum1[s][i] + grid[i][j];
            }
        }
        for (int d = m - 1; d >= -n + 1; d--) {
            for (int i = max(d, 0); i < m; i++) {
                int j = i - d;  // j 越来越大
                if (j >= n) break;
                sum2[d + OFFSET][i + 1] = sum2[d + OFFSET][i] + grid[i][j];
            }
        }

        set<int> s;
        for (int r = 0; r <= (m - 1) / 2; r++) {
            for (int i = r; i + r < m; i++) {
                for (int j = r; j + r < n; j++) {
                    int top = i - r, left = j - r, down = i + r, right = j + r;
                    int s1 = top + j, s2 = down + j;
                    int d1 = i - right, d2 = i - left;
                    int ans1 = sum1[s1][i + 1] - sum1[s1][top];
                    int ans2 = sum1[s2][down + 1] - sum1[s2][i];
                    int ans3 = sum2[d1 + OFFSET][i + 1] - sum2[d1 + OFFSET][top];
                    int ans4 = sum2[d2 + OFFSET][down + 1] - sum2[d2 + OFFSET][i];
                    int ans = ans1 + ans2 + ans3 + ans4;
                    if (r > 0) {
                        ans = ans - grid[i][left] - grid[i][right] - grid[top][j] - grid[down][j];
                    } else {
                        ans = ans - grid[i][left] - grid[i][right] - grid[top][j];
                    }
                    // cout << r << " " << i << " " << j << " (" << ans1 << " " << ans2 << " " << ans3 << " " << ans4 << ") " << ans << endl;
                    s.insert(ans);
                }
            }
        }
        vector<int> ans;
        for (auto it = s.rbegin(); it != s.rend(); it++) {
            if (ans.size() == 3) return ans;
            ans.push_back(*it);
        }
        return ans;
    }
};
