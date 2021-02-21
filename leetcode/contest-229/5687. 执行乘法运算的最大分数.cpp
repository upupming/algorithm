#include <bits/stdc++.h>
using namespace std;
const int M = 1e3 + 10;
int f[M][M];
/*
f[i][j] 表示 nums 从 i 开始，multiplier 从 j 开始的所有可能方案的最大分数
，nums 末尾被使用的数的个数一定是 (j-i)。

注意到从前面数和从后面数，下标大于 2*10^3 的 nums[i] 一定不会被访问，因此数组 f 只用开到 m*m 维即可（开成 n*m 会 TLE）
*/
class Solution {
    int n, m;

   public:
    int maximumScore(vector<int>& nums, vector<int>& mul) {
        n = nums.size(), m = mul.size();
        memset(f, 0, sizeof f);
        for (int j = m - 1; j >= 0; j--) {
            for (int i = 0; i <= j; i++) {
                f[i][j] = max(
                    f[i + 1][j + 1] + nums[i] * mul[j],
                    f[i][j + 1] + (nums[n - (j - i) - 1]) * mul[j]);
            }
        }
        return f[0][0];
    }
};
