#include <bits/stdc++.h>
using namespace std;
// dfs + 剪枝
class Solution {
    int m, st[100], used[100];
    vector<int> ans;

    bool dfs(int x, int n) {
        if (x >= m) return true;
        for (int i = n; i >= 1; i--) {
            if (used[i]) continue;
            if (i == 1) {
                st[x] = 1;
                ans[x] = 1;
                used[i] = 1;

                int y = x + 1;
                while (st[y]) y++;
                if (dfs(y, n)) return true;
                used[i] = 0;
                st[x] = 0;
            } else {
                if (x + i < m && !st[x + i]) {
                    st[x] = st[x + i] = 1;
                    ans[x] = ans[x + i] = i;
                    used[i] = 1;

                    int y = x + 1;
                    while (st[y]) y++;
                    if (dfs(y, n)) return true;

                    st[x] = st[x + i] = 0;
                    used[i] = 0;
                }
            }
        }
        return false;
    }

   public:
    vector<int> constructDistancedSequence(int n) {
        // 长度肯定是 2 * (n-1) +1
        m = 2 * (n - 1) + 1;
        memset(st, 0, sizeof st);
        memset(used, 0, sizeof used);
        ans.resize(m);
        dfs(0, n);
        return ans;
    }
};