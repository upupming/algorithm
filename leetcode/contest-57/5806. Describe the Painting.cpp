#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class Solution {
   public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        int l = INT_MAX, r = 0;
        set<int> x;
        for (auto& s : segments) {
            l = min(l, s[0]);
            r = max(r, s[1]);
            x.insert(s[0]), x.insert(s[1]);
        }
        vector<LL> diff(r + 1);
        for (auto& s : segments) {
            diff[s[0]] += s[2];
            diff[s[1]] -= s[2];
        }
        vector<vector<long long>> ans;
        LL cur = -1, idx = -1;
        for (int i = l; i <= r; ++i) {
            diff[i] += diff[i - 1];
            if (cur == -1)
                cur = diff[i], idx = i;
            else {
                if (x.count(i)) {
                    if (cur > 0)
                        ans.push_back({idx, i, cur});
                    cur = diff[i], idx = i;
                }
            }
        }
        return ans;
    }
};
