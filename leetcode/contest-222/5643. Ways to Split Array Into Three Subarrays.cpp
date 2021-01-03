#include <bits/stdc++.h>
using namespace std;

/*
两个分割点，枚举第一个分割点，二分第二个分割点（最远和最近）即可
前缀和加速处理
*/
class Solution {
   public:
    const int MOD = 1e9 + 7;
    int waysToSplit(vector<int>& nums) {
        int n = nums.size();
        vector<int> sum(n + 1);
        for (int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];
        long long ans = 0;
        for (int i = 1; i < n; i++) {
            // cout << i << endl;
            int x = sum[i], y, z, leftMost, rightMost;

            // 先枚举最近的地方
            int l = i + 1, r = n;
            while (l < r) {
                int mid = (l + r - 1) >> 1;
                if (sum[mid] - sum[i] >= x)
                    r = mid;
                else
                    l = mid + 1;
            }
            y = sum[l] - sum[i];
            z = sum[n] - sum[l];
            // cout << y << " " << z << endl;
            // 无解
            if (z < y || y < x || l == n) continue;
            leftMost = l;

            // 再枚举最远的地方
            l = i + 1, r = n - 1;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (sum[n] - sum[mid] >= sum[mid] - sum[i])
                    l = mid;
                else
                    r = mid - 1;
            }
            y = sum[l] - sum[i];
            z = sum[n] - sum[l];
            // cout << y << " " << z << endl;
            // 无解
            if (z < y || y < x || r == n) continue;
            rightMost = l;

            // cout << i << " " << leftMost << " " << rightMost << endl;
            ans += (rightMost - leftMost + 1);
            ans %= MOD;
        }
        return ans;
    }
};