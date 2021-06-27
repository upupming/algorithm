#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10, M = 1030;
// 前缀和，需要滚动更新，正常来说应该是 sum[i][m] 表示 1~i 中数 m 的个数，但是需要优化成 m 的长度时间才能过
// 注意到只需要使用 sum[i][m] - sum[0][m] 判断 i~j 中的 m 的个数，所以可以省去一维
// 用数 m 每一位表示累计的字母的个数是奇数还是偶数，奇数用 1 表示，偶数用 0 表示
int sum[M];
class Solution {
   public:
    long long wonderfulSubstrings(string word) {
        int n = word.length();
        memset(sum, 0, sizeof sum);
        LL ans = 0;
        int f = 0;
        // 考试的时候漏了这个边界，所以出问题了
        sum[f] += 1;
        for (int i = 1; i <= n; i++) {
            f ^= (1 << (word[i - 1] - 'a'));
            int tmp = sum[f];
            for (int j = 0; j < 10; j++) {
                int g = f ^ (1 << j);
                tmp += sum[g];
            }
            ans += tmp;
            sum[f] += 1;
        }
        return ans;
    }
};
