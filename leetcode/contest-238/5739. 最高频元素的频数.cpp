#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class Solution {
   public:
    vector<int> nums;
    vector<LL> sum;
    int k;
    bool valid(int mid, int i) {
        LL sec = sum[i] - sum[mid - 1];
        return (i - mid + 1ll) * nums[i - 1] - sec <= k;
    }
    int maxFrequency(vector<int>& _nums, int _k) {
        nums = _nums, k = _k;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        sum.resize(n + 1);
        for (int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int l = 1, r = i;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (valid(mid, i)) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            ans = max(ans, i - l + 1);
        }
        return ans;
    }
};
