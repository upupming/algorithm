#include <bits/stdc++.h>
using namespace std;
/*
1. 将 queries 排序，从小到大处理，每处理一个 query，将 <= m_i 的 num 放入 trie 数中
2. 剩下的步骤就是求最大异或对了
*/
const int N = 32 * 1e5 + 10;
int trie[N][2], tot = 1;
// O(1e5)
void init_trie() {
    memset(trie, 0, sizeof trie);
    tot = 1;
}
// O(32)
void insert(int x) {
    int p = 1;
    for (int i = 31; i >= 0; i--) {
        int j = x >> i & 1;
        if (trie[p][j] == 0) trie[p][j] = ++tot;
        p = trie[p][j];
    }
}
// O(32)
int max_xor(int x) {
    int p = 1, q = 1;
    int ans = 0;
    for (int i = 31; i >= 0; i--) {
        int j = x >> i & 1;
        p = trie[p][j];
        if (trie[q][!j]) {
            q = trie[q][!j];
            ans |= 1 << i;
        } else {
            q = trie[q][j];
        }
    }
    return ans;
}
class Solution {
   public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), m = queries.size();
        init_trie();

        sort(nums.begin(), nums.end());
        for (int i = 0; i < m; i++) {
            queries[i].push_back(i);
        }
        sort(queries.begin(), queries.end(), [&queries](auto& a, auto& b) {
            return a[1] < b[1];
        });

        vector<int> ans(m, -1);
        for (int i = 0, j = 0; i < m; i++) {
            while (j < n && nums[j] <= queries[i][1]) {
                insert(nums[j]);
                j++;
            }
            if (j > 0)
                ans[queries[i][2]] = max_xor(queries[i][0]);
        }
        return ans;
    }
};
