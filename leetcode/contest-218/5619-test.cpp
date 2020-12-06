#include <iostream>
#include <vector>
using namespace std;
class Solution {
   public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        int inf = 1e8, n = nums.size();
        // f[i] 表示 i 表示的集合的答案，f[i] = min(f[i], f[j] + f[i-j])，所有方案最优解
        vector<int> f(1 << n, inf);
        vector<bool> baseCases(1 << n, false);

        // 枚举所有子集
        for (int i = 0; i < 1 << n; i++) {
            // 刚好 n/k  个数
            if (__builtin_popcount(i) == n / k) {
                // 用位表示是否存在某个数，由于数 <= 16， int 足够
                int visited = 0, minVal = 16, maxVal = 0, ok = 1;
                for (int j = 0; j < n; j++) {
                    if ((i >> j) & 1) {
                        // 有重复的数，子集不合法
                        if (visited & (1 << nums[j])) {
                            ok = false;
                            break;
                        }
                        maxVal = max(maxVal, nums[j]);
                        minVal = min(minVal, nums[j]);
                        visited |= 1 << nums[j];
                    }
                }
                if (ok) {
                    f[i] = maxVal - minVal;
                    baseCases[i] = true;
                }
            }
        }

        // dp 计算过程
        // 基础情况
        f[0] = 0;
        // 递推过程
        for (int i = 0; i < 1 << n; i++) {
            // 枚举 i 的所有子集
            for (int j = i; j; j = (j - 1) & i) {
                if (baseCases[j]) {
                    f[i] = min(f[i - j] + f[j], f[i]);
                }
            }
        }
        // 这里不打小括号会出错，优先级不对
        return f[(1 << n) - 1] == inf ? -1 : f[(1 << n) - 1];
    }
};

int main() {
    vector<int> nums{6, 8, 5, 16, 8, 12, 11, 7, 13, 16, 15, 14, 7, 9, 1, 10};
    int k = 4;
    cout << Solution().minimumIncompatibility(nums, k) << endl;

    return 0;
}