#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int m = box.size(), n = box[0].size();
        vector<vector<char>> ans(n, vector<char>(m));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans[i][j] = box[m - 1 - j][i];
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < m; j++) {
                if (ans[i][j] != '#') continue;
                int k = i + 1;
                while (k < n && ans[k][j] == '.') {
                    swap(ans[k][j], ans[k - 1][j]);
                    k++;
                }
            }
        }
        return ans;
    }
};
