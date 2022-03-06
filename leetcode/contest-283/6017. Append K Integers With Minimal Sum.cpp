#include <set>
#include <vector>
using namespace std;
class Solution {
   public:
    long long minimalKSum(vector<int>& nums, int k) {
        set<int> s;
        for (auto x : nums) {
            s.insert(x);
        }
        nums.clear();
        for (auto x : s) nums.push_back(x);

        sort(nums.begin(), nums.end());
        int cnt, last;
        long long ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i == 0) {
                cnt = nums[i] - 1, last = 1;
            } else {
                cnt = nums[i] - nums[i - 1] - 1, last = nums[i - 1] + 1;
            }
            if (k > cnt) {
                k -= cnt;
                ans += (last + (last + cnt - 1ll)) * cnt / 2;
            } else {
                ans += (last + (last + k - 1ll)) * k / 2;
                k = 0;
            }
        }
        last = nums.back() + 1;
        if (k) ans += (last + (last + k - 1ll)) * k / 2;
        return ans;
    }
};
