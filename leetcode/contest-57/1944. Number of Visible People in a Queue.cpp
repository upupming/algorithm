#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        int n = heights.size();
        heights.push_back(1e6);
        vector<int> ans(n, 0), right(n, 0);

        stack<int> s({n});
        for (int i = n - 1; i >= 0; --i) {
            while (heights[s.top()] < heights[i]) {
                s.pop();
                ans[i]++;
            }
            // 可以看到一个比他高的
            if (s.top() != n) ans[i]++;
            s.push(i);
        }
        return ans;
    }
};
