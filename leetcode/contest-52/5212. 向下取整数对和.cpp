#include <bits/stdc++.h>
using namespace std;
const int P = 1e9 + 7;
typedef long long LL;
class Solution {
   public:
    int sumOfFlooredPairs(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        nums.insert(nums.begin(), -1);
        nums.push_back(INT_MAX);

        LL ans = 0, last = -1;
        for (int i = 1; i <= n; i++) {
            if (nums[i] == nums[i - 1]) {
                ans = (ans + last) % P;
                continue;
            }
            last = 0;
            LL a = nums[i];
            // j 的次数: ?/a=j
            for (int j = 0;; j++) {
                LL x = (j + 1ll) * a;
                // 找到 < x 的最右边
                int l = 0, r = n + 1;
                while (l < r) {
                    int mid = (l + r + 1) >> 1;
                    if (nums[mid] < x)
                        l = mid;
                    else
                        r = mid - 1;
                }
                int tmp = l;
                // >=y 的最左边
                LL y = (LL)j * a;
                l = 0, r = n + 1;
                while (l < r) {
                    int mid = (l + r) >> 1;
                    if (nums[mid] >= y)
                        r = mid;
                    else
                        l = mid + 1;
                }
                if (l == n + 1) break;
                if (tmp >= l) {
                    ans = (ans + (tmp - l + 1ll) * j) % P;
                    last += (tmp - l + 1ll) * j;
                }
            }
        }
        return ans;
    }
};
