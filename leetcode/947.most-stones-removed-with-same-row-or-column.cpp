/*
 * @lc app=leetcode id=947 lang=cpp
 *
 * [947] Most Stones Removed with Same Row or Column
 */

#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
   public:
    int removeStones(vector<vector<int>>& stones) {
        map<int, map<int, bool>> m, m1;
        map<int, map<int, int>> parent;

        int rows = 0, cols = 0;
        for (auto stone : stones) {
            m[stone[0]][stone[1]] = true;
            m1[stone[1]][stone[0]] = true;
            parent[stone[0]][stone[1]] = -1;
        }

        int ans = 0;

        for (auto mi : m) {
            int i = mi.first;
            for (auto mj : mi.second) {
                int j = mj.first;

                int curRoot = find(parent, i, j);
                int xi = i, xj = j;
                // cout << "curRoot: " << curRoot % 10000 << ", " << curRoot / 10000 << endl;

                // Same row
                for (auto point : mi.second) {
                    int xj = point.first;
                    if (!m[xi][xj] || !(xj > j)) continue;
                    int xRoot = find(parent, xi, xj);
                    // cout << "xRoot: " << xRoot % 10000 << ", " << xRoot / 10000 << endl;
                    if (curRoot != xRoot) {
                        parent[xRoot % 10000][xRoot / 10000] = curRoot;
                        // cout << "union for " << i << ", " << j << "; " << xi << ", " << xj << endl;
                        ans++;
                        // assert(find(parent, i, j) == find(parent, xi, xj));
                    }
                }
                // Same column
                for (auto point : m1[j]) {
                    int xi = point.first;
                    if (!m[xi][xj] || !(xi > i)) continue;
                    int xRoot = find(parent, xi, xj);
                    // cout << "xRoot: " << xRoot % 10000 << ", " << xRoot / 10000 << endl;
                    if (curRoot != xRoot) {
                        parent[xRoot % 10000][xRoot / 10000] = curRoot;
                        // cout << "union for " << i << ", " << j << "; " << xi << ", " << xj << endl;
                        ans++;
                        // assert(find(parent, i, j) == find(parent, xi, xj));
                    }
                }
            }
        }

        return ans;
    }
    int find(map<int, map<int, int>>& parent, int i, int j) {
        if (parent[i][j] == -1)
            return i + j * 10000;
        else
            return find(parent, parent[i][j] % 10000, parent[i][j] / 10000);
    }
};
// @lc code=end
