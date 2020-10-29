
// https://leetcode.com/contest/weekly-contest-212/problems/path-with-minimum-effort/
#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();

        //  (m + n) vertices, [0, m) represents rows [0, m) and [m, m + n) represents cols [0, n)
        vector<int> rank(m + n);
        vector<vector<int>> ans(m, vector<int>(n));

        // Generate edges with same matrix value
        map<int, vector<int>> mp;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                mp[matrix[i][j]].push_back(i * n + j);
            }
        }

        // For edges with smaller value to larger value
        for (auto& a : mp) {
            // Root array
            vector<int> root(m + n);
            // init root[i] = i
            iota(root.begin(), root.end(), 0);

            auto values = a.second;
            for (auto& v : values) {
                int i = v / n, j = v % n;
                cout << "(i, j) = (" << i << ", " << j << ")" << endl;
                // find the root for vertex i and j + m
                int r1 = find(root, i), r2 = find(root, j + m);
                // make row vertex point to column vertex
                root[r1] = r2;
                cout << "set root of " << r1 << " to " << r2 << endl;
                // update the root's rank
                rank[r2] = max(rank[r1], rank[r2]);
                cout << "update rank of " << r2 << " to " << rank[r2] << endl;
            }

            // make a deep copy for the convenience of calculation
            auto rank2 = rank;
            for (auto& v : values) {
                int i = v / n, j = v % n;
                cout << "(i, j) = (" << i << ", " << j << ")" << endl;
                int r = find(root, i);
                cout << "found root of " << i << " is " << r << endl;
                ans[i][j] = rank[r] + 1;
                cout << "update ans[" << i << "][" << j << "] to " << ans[i][j] << endl;
                rank2[i] = rank[r] + 1;
                cout << "update rank2[" << i << "] to " << ans[i][j] << endl;
                rank2[j + m] = rank[r] + 1;
                cout << "update rank2[" << j + m << "] to " << rank2[j + m] << endl;
            }
            rank = move(rank2);
        }
        return ans;
    }
    int find(const vector<int>& root, int i) {
        if (root[i] != i) return find(root, root[i]);
        return root[i];
    }
};