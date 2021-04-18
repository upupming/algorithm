#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
class Solution {
    int dist(PII a, PII b) {
        int x = a.first - b.first;
        int y = a.second - b.second;
        return x * x + y * y;
    }

   public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        int n = points.size(), m = queries.size();
        vector<int> ans(m);
        for (int i = 0; i < m; i++) {
            PII o{queries[i][0], queries[i][1]};
            int r_2 = queries[i][2] * queries[i][2];
            for (int j = 0; j < n; j++) {
                int d = dist(o, {points[j][0], points[j][1]});
                if (d <= r_2) ans[i]++;
            }
        }
        return ans;
    }
};
