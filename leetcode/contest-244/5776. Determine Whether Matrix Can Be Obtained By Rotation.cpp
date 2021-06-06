#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        int n = mat.size();
        vector<vector<int>> tmp = mat;
        for (int k = 0; k < 5; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    tmp[j][n - 1 - i] = mat[i][j];
                }
            }
            mat = tmp;

            bool ok = true;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (mat[i][j] != target[i][j]) {
                        ok = false;
                        break;
                    }
                }
            }
            if (ok) return true;
        }
        return false;
    }
};
