#include <bits/stdc++.h>
using namespace std;

/*
上次比赛也是排序 5632. Checking Existence of Edge Length Limited Paths
以后看到 query 查询操作就要想到能不能离线处理，先排序再说

思路不要想太复杂，想太复杂往往就错了
*/
const int N = 1e5 + 10, M = 32 * N;
class Solution {
    int trie[M][2], p, tsize = 1;

    void insert(int a) {
        p = 1;
        for (int i = 31; i >= 0; i--) {
            int j = a >> i & 1;
            if (trie[p][j] == 0) trie[p][j] = ++tsize;
            p = trie[p][j];
        }
    }

   public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        int n = queries.size();
        vector<int> ans(n, 0);
        typedef pair<int, int> PII;
        vector<PII> q;
        for (int i = 0; i < n; i++)
            q.emplace_back(queries[i][1], i);
        sort(q.begin(), q.end());
        sort(nums.begin(), nums.end());

        for (int i = 0, j = 0; i < n; i++) {
            while (j < n && nums[j] <= q[i].first) {
                insert(nums[j]);
                j++;
            }
            int idx = q[i].second;
            if (j == 0) {
                ans[idx] = -1;
                continue;
            }
            int x = queries[idx][0];
            p = 1;
            for (int k = 31; k >= 0; k--) {
                int bit = x >> k & 1;
                if (trie[p][!bit]) {
                    ans[idx] |= 1 << k;
                    p = trie[p][!bit];
                } else {
                    p = trie[p][bit];
                }
            }
        }

        return ans;
    }
};