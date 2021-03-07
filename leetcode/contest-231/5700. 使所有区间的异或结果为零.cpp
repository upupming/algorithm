#include <bits/stdc++.h>
using namespace std;

/*
1 2 3 4 5 6 7 8 9 10, k = 3
调整后，每 3 个数必然形成一个周期（异或的性质）
先排成矩阵形式再做处理，i%k 表示所处的列：
1 2 3
4 5 6
7 8 9
10

f[i][j] 表示前 i 列中，异或值为 j 时的最少修改次数，其中 i 的范围是 [0, k)，j 的范围是 [0, 1024)

初始时：
f[0][j] = cnt[0]
f[0][k] = cnt[0] - p[0][k]（已经满足的不需要修改）
其余为正无穷
转移时：
f[i][j] = min(
    f[i-1][t] + cnt[i]
)
min(f[i-1[t]]) 可以用 g 来存储
也可以通过这一位上已经有的数字 k，从 f(i−1,j xor k)+cnt(i)−p(i,k) 进行转移。
答案：f[k-1][0]
*/

class Solution {
   public:
    int minChanges(vector<int>& nums, int k) {
        int n = nums.size();
        // p[i%k] 是一个 map，用来表示第 i%k 列中每个数字出现的次数
        vector<unordered_map<int, int>> p(k);
        // sum[i%k] 则表示这一列有多少个数
        vector<int> cnt(k, 0);
        for (int i = 0; i < n; i++) {
            p[i % k][nums[i]]++;
            cnt[i % k]++;
        }

        vector<vector<int>> f(k, vector<int>(1024, INT_MAX));
        vector<int> g(k, INT_MAX);
        for (int j = 0; j < 1024; j++) {
            f[0][j] = cnt[0];
            g[0] = min(g[0], f[0][j]);
        }

        for (auto& [k, v] : p[0]) {
            f[0][k] = cnt[0] - v;
            g[0] = min(g[0], f[0][k]);
        }

        for (int i = 1; i < k; i++) {
            for (int j = 0; j < 1024; j++) {
                f[i][j] = g[i - 1] + cnt[i];

                for (auto& [k, v] : p[i]) {
                    // 异或和从 j^k 变成 j，需要异或上 k 即可，所以需要减去已经是 k 的个数 v
                    f[i][j] = min(
                        f[i][j],
                        f[i - 1][j ^ k] + cnt[i] - v);
                }
                g[i] = min(g[i], f[i][j]);
            }
        }

        return f[k - 1][0];
    }
};
