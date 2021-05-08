#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> h(n, 0);
        int res = 0;
        for (int i = 0; i < m; i++) {
            multiset<int> s;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0)
                    h[j] = 0;
                else
                    h[j] += 1;
                s.insert(h[j]);
            }
            int cnt = 1, ans = 0;
            for (auto it = s.rbegin(); it != s.rend() && *it != 0; it++, cnt++) {
                ans = max(ans, cnt * (*it));
            }
            res = max(res, ans);
        }
        return res;
    }
};
