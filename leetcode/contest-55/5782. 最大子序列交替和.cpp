#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class Solution {
   public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        // vector<LL> f(n + 1), g(n + 1);
        priority_queue<LL> pf, pg;
        for (int i = 0; i < n; i++) {
            LL tmpf = 0, tmpg = 0;
            if (i == 0) {
                tmpf = nums[i];
            } else {
                tmpf = pg.top() + nums[i];
                tmpg = pf.top() - nums[i];
            }
            pf.push(tmpf);
            pg.push(tmpg);
        }
        return max(pf.top(), pg.top());
    }
};
