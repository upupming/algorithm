class Solution {
public:
    int oddCells(int n, int m, vector<vector<int>>& indices) {
        vector<vector<int>> ma(n, vector<int>(m, 0));
        for (int i = 0; i < indices.size(); i++) {
            int ri = indices[i][0];
            int ci = indices[i][1];
            for (int j = 0; j < m; j++) {
                ma[ri][j]++;
            }
            for (int j = 0; j < n; j++) {
                ma[j][ci]++;
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans += (ma[i][j] % 2 == 1);
            }
        }
        return ans;
    }
};