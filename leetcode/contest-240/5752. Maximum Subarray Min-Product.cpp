#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int P = 1e9 + 7;
class Solution {
   public:
    vector<LL> sum;
    vector<int> nums, left, right;
    int n;
    int maxSumMinProduct(vector<int>& _nums) {
        nums = _nums;
        n = nums.size();
        sum.resize(n + 1, 0);
        left.resize(n + 1, 0);
        right.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
        stack<int> s;
        nums.insert(nums.begin(), -1);
        s.push(0);
        for (int i = 1; i <= n; i++) {
            while (nums[s.top()] >= nums[i]) s.pop();
            left[i] = s.top();
            // cout << i << " " << nums[i] << " " << left[i] << " " << nums[left[i]] << endl;
            s.push(i);
        }
        nums.push_back(-1);
        s = stack<int>();
        s.push(n + 1);
        for (int i = n; i >= 1; i--) {
            while (nums[s.top()] >= nums[i]) s.pop();
            right[i] = s.top();
            // cout << i << " " << nums[i] << " " << right[i] << " " << nums[right[i]] << endl;
            s.push(i);
        }
        LL ans = 0;
        for (int i = 1; i <= n; i++) {
            // cout << i << " " << left[i] + 1 << " " << right[i]-1 << endl;
            ans = max(ans, (sum[right[i] - 1] - sum[left[i]]) * nums[i]);
        }
        return ans % P;
    }
};
