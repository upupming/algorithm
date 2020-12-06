#include <algorithm>
#include <vector>
using namespace std;
/*
位运算 + 状态压缩 dp + 集合枚举
每个二进制数可以表示所有数据的一个子集，比如对于：
nums = [6, 3, 8, 1, 3, 1, 2, 2]
b =    [0, 1, 0, 1, 0, 1, 0, 1]
b 就是代表着子集 {3, 1, 1, 2}
最终要分为大小为 m = num.size() / k 的 k 组数
用 dp[b] 表示：将 b 代表的子集分成若干大小为 m 的组时的答案
如果已经知道子问题 tb 和 b-tb 的答案，那么：
dp[b] = min(dp[b - tb] + dp[tb], dp[b])
min 意味着取所有的划分方案里面，结果最小划分方案

例如：
b =    [0, 1, 0, 1, 0, 1, 0, 1]
tb =   [0, 1, 0, 1, 0, 0, 0, 0]
b - tb=[0, 0, 0, 0, 0, 1, 0, 1]

可以先预处理所有大小为 m 的数对，求出 incompatibilities
最终的答案就是 dp[1 << nums.size() - 1]，1 << nums.size() - 1 是所有数的集合表示

失误：刚开始想了错误的揭发 + 后来想了 TLE 的揭发，最终一小时还是没 AC
*/

// y 总讲到枚举子集的关键在于：for (int j = i; j; j = j - 1 & i) {
// 所以可以重新做一遍了

class Solution {
   public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        int inf = 1e8, n = nums.size();
        // f[i] 表示 i 表示的集合的答案，f[i] = min(f[i], f[j] + f[i-j])，所有方案最优解
        vector<int> f(1 << n, inf);
        vector<int> g(1 << n, -1);

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
                    g[i] = maxVal - minVal;
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
                if (g[j] != -1) {
                    f[i] = min(f[i - j] + g[j], f[i]);
                }
            }
        }
        // 这里不打小括号会出错，优先级不对
        return f[(1 << n) - 1] == inf ? -1 : f[(1 << n) - 1];
    }
};

/*
class Solution {
   public:
    int per, n;

    int numOfOnes(int x) {
        int ans = 0;
        while (x > 0) {
            ans += x & 1, x >>= 1;
        }
        return ans;
    }
    int minimumIncompatibility(vector<int>& nums, int k) {
        n = nums.size(), per = nums.size() / k;

        vector<int> dp(1 << n, INT_MAX);
        vector<pair<int, int>> ic;
        // 预处理计算所有的 incompatibilities
        for (int i = 0; i < 1 << n; i++) {
            // 只有刚好为 per 个数的情况，才是合格的一组
            if (numOfOnes(i) == per) {
                bool noSameNum = true;
                int maxVal = INT_MIN, minVal = INT_MAX, visited = 0;
                for (int j = 0; j < n; j++) {
                    if ((i >> j) & 1) {
                        if (visited & (1 << nums[j])) {
                            noSameNum = false;
                            break;
                        }
                        maxVal = max(maxVal, nums[j]);
                        minVal = min(minVal, nums[j]);
                        visited |= (1 << nums[j]);
                    }
                }
                if (noSameNum) {
                    ic.emplace_back(i, maxVal - minVal);
                    dp[i] = maxVal - minVal;
                }
            }
        }
        dp[0] = 0;
        for (int i = 0; i < 1 << n; i++) {
            if (numOfOnes(i) % per == 0) {
                for (int j = 0; j < ic.size(); j++) {
                    int tb = ic[j].first;
                    if (i >= tb && ((tb & i) == tb)) {
                        if (dp[i - tb] != INT_MAX) {
                            dp[i] = min(dp[tb] + dp[i - tb], dp[i]);
                        }
                    }
                }
            }
        }
        return dp[(1 << n) - 1] == INT_MAX ? -1 : dp[(1 << n) - 1];
    }
};
*/