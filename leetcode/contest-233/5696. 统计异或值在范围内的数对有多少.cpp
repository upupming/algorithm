#include <bits/stdc++.h>
using namespace std;
using namespace std;
const int N = 15 * 2 * 1e4 + 10;
int trie[N][2], n, a, tot = 1, p, cnt[N];
class Solution {
    vector<int> nums;
    int n;
    // 计算有多少数和 x 异或之后 > maxXor
    int dfs(int x, int p, int q, int curXor, int k, int maxXor) {
        if (k == -1) return 0;
        int j = x >> k & 1;
        p = trie[p][j];
        int ans = 0;
        // 寻找匹配，能够匹配一个不同的位的话
        if (trie[q][!j]) {
            int newXor = curXor | 1 << k;
            int newQ = trie[q][!j];
            if (newXor > maxXor)
                ans += cnt[newQ];
            // 后续即使全部为 1 也无法达到 maxXor，提前剪枝
            else if (newXor + (1 << k) - 1 > maxXor) {
                ans += dfs(x, p, newQ, newXor, k - 1, maxXor);
            }
        }
        // 后续即使全部为 1 也无法达到 maxXor，提前剪枝
        if (curXor + (1 << k) - 1 > maxXor) {
            // 匹配一个相同的位
            int newQ = trie[q][j];
            ans += dfs(x, p, newQ, curXor, k - 1, maxXor);
        }
        return ans;
    }
    // 有多少对的异或值在 [0, maxXor] 之间
    int solve(int maxXor) {
        int ans = 0;
        for (auto& a : nums) {
            ans += dfs(a, 1, 1, 0, 15, maxXor);
        }
        // cout << maxXor << ", " << ans << "," << (n * (n - 1) / 2 - ans / 2) << endl;
        return n * (n - 1) / 2 - ans / 2;
    }

   public:
    int countPairs(vector<int>& _nums, int low, int high) {
        nums = _nums, n = nums.size();
        memset(trie, 0, sizeof trie);
        memset(cnt, 0, sizeof cnt);
        int ans = 0;
        tot = 1;
        for (auto& a : nums) {
            p = 1, cnt[p]++;
            for (int i = 15; i >= 0; i--) {
                int j = a >> i & 1;
                if (trie[p][j] == 0) trie[p][j] = ++tot;
                p = trie[p][j];
                cnt[p]++;
            }
        }

        return solve(high) - solve(low - 1);
    }
};
