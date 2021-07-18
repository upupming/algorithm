#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
LL dp_add[2][N], dp_minus[2][N];
LL add_max[2][N], minus_max[2][N];
class Solution {
   public:
    long long maxPoints(vector<vector<int>>& points) {
        int m = points.size(), n = points[0].size();

        LL ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, (LL)points[0][i]);
            dp_add[0][i] = points[0][i] + i;
            add_max[0][i] = max(i == 0 ? (LL)-1e9 : add_max[0][i - 1], dp_add[0][i]);
        }
        for (int i = n - 1; i >= 0; i--) {
            dp_minus[0][i] = points[0][i] - i;
            minus_max[0][i] = max(i == n - 1 ? (LL)-1e9 : minus_max[0][i + 1], dp_minus[0][i]);
        }

        for (int i = 1; i < m; i++) {
            ans = 0;
            for (int j = 0; j < n; j++) {
                dp_add[1][j] = dp_minus[1][j] = max(
                    add_max[0][j] + (points[i][j] - j),
                    minus_max[0][j] + (points[i][j] + j));
                ans = max(dp_add[1][j], ans);
            }
            for (int i = 0; i < n; i++) {
                dp_add[1][i] += i;
                add_max[1][i] = max(i == 0 ? (LL)-1e9 : add_max[1][i - 1], dp_add[1][i]);
            }
            for (int i = n - 1; i >= 0; i--) {
                dp_minus[1][i] -= i;
                minus_max[1][i] = max(i == n - 1 ? (LL)-1e9 : minus_max[1][i + 1], dp_minus[1][i]);
            }
            for (int j = 0; j < n; j++) {
                dp_add[0][j] = dp_add[1][j];
                dp_minus[0][j] = dp_minus[1][j];
                add_max[0][j] = add_max[1][j];
                minus_max[0][j] = minus_max[1][j];
            }
            // cout << i << " " << ans << endl;
        }
        return ans;
    }
};
