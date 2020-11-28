#include <vector>
using namespace std;

// 最长单调子序列算法
// 数据量 10^3 比较小，可以直接用 dp O(n^2) 的算法，不需要用 O(n log n) 的贪心
// f[k]: 以 k 结尾的最长上升子序列的长度
// g[k]: 以 k 开头的最长上升子序列的长度
// argmax f[k] + g[k] - 1, st. f[k] > 1, g[k] > 1
class Solution {
   public:
    int minimumMountainRemovals(vector<int>& nums) {
        vector<int> f(nums.size(), 1), g(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j])
                    f[i] = max(f[i], f[j] + 1);
            }
        }
        for (int i = nums.size() - 2; i >= 0; i--) {
            for (int j = nums.size() - 1; j > i; j--) {
                if (nums[i] > nums[j])
                    g[i] = max(g[i], g[j] + 1);
            }
        }
        int maxCnt = 0;
        for (int i = 0; i < nums.size(); i++) {
            // cout << f[i] << ", " << g[i] << ", " << f[i] + g[i] - 1 << endl;
            // 必须有坡
            if (f[i] > 1 && g[i] > 1) {
                maxCnt = max(maxCnt, f[i] + g[i] - 1);
            }
        }
        return nums.size() - maxCnt;
    }
};