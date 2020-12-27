#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int minMoves(vector<int>& nums, int k) {
        vector<int> a;
        for (int i = 0; i < nums.size(); i++)
            if (nums[i]) a.push_back(i - a.size());
        int n = a.size();
        typedef long long LL;
        vector<LL> s(n + 1);
        for (int i = 1; i <= n; i++)
            s[i] = s[i - 1] + a[i - 1];
        LL res = LONG_LONG_MAX;
        for (int i = k; i <= n; i++) {
            int l = i - k + 1, r = i;
            int mid = (l + r) >> 1;
            LL x = a[mid - 1];
            LL left = x * (mid - l) - (s[mid - 1] - s[l - 1]);
            LL right = (s[r] - s[mid]) - x * (r - mid);
            res = min(res, left + right);
        }
        return res;
    }
};