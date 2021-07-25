#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<vector<int>> students, mentors;
    vector<int> v;
    vector<vector<int>> f;
    int score(int i, int j) {
        if (f[i][j] != -1) return f[i][j];
        int ans = 0;
        for (int k = 0; k < students[i].size(); ++k) {
            ans += (students[i][k] == mentors[j][k]) ? 1 : 0;
        }
        return f[i][j] = ans;
    }
    int dfs(int cur, int com) {
        if (cur == v.size()) return com;
        int ans = 0;
        for (int i = 0; i < mentors.size(); i++) {
            if (!v[i]) {
                v[i] = 1;
                int res1 = dfs(cur + 1, com + score(cur, i));
                ans = max(ans, res1);
                v[i] = 0;
            }
        }
        return ans;
    }
    int maxCompatibilitySum(vector<vector<int>>& _students, vector<vector<int>>& _mentors) {
        students = _students, mentors = _mentors;
        int n = students.size();
        f.resize(n, vector<int>(n, -1));
        v.resize(n, 0);
        return dfs(0, 0);
    }
};
