#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int orientation(vector<int> &p, vector<int> &q, vector<int> &r) {
        return (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
    }
    vector<vector<int>> outerTrees(vector<vector<int>> &trees) {
        set<vector<int>> ans;
        if (trees.size() < 4) {
            for (auto &tree : trees) {
                ans.insert(tree);
            }
            return {ans.begin(), ans.end()};
        }
        int leftMost = 0;
        for (int i = 0; i < trees.size(); i++) {
            if (trees[i][0] < trees[leftMost][0]) {
                leftMost = i;
            }
        }
        int p = leftMost;
        do {
            int q = (p + 1) % trees.size();
            for (int i = 0; i < trees.size(); i++) {
                if (orientation(trees[p], trees[i], trees[q]) < 0) {
                    q = i;
                }
            }
            // 如果有一些是 between 的，也要加上
            for (int i = 0; i < trees.size(); i++) {
                if (i != p && i != q && orientation(trees[p], trees[q], trees[i]) == 0) {
                    ans.insert(trees[i]);
                }
            }
            ans.insert(trees[q]);
            p = q;
        } while (p != leftMost);
        return {ans.begin(), ans.end()};
    }
};
