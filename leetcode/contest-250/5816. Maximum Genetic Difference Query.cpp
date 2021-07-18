#include <bits/stdc++.h>
using namespace std;

// 晚了一分钟 AC，太可惜了，在第 3 题花了太长的时间

const int N = 20 * (1e5 + 10);
int trie[N][2], tot = 1, cnt[N];
void insert(int a, int v) {
    int p = 1;
    for (int i = 30; i >= 0; i--) {
        int j = a >> i & 1;
        if (trie[p][j] == 0) {
            trie[p][j] = ++tot;
        }
        p = trie[p][j];
        cnt[p] += v;
    }
}

int query(int a) {
    int ans = 0, p = 1;
    for (int i = 30; i >= 0; i--) {
        int j = a >> i & 1;
        if (cnt[trie[p][!j]]) {
            p = trie[p][!j];
            ans |= 1 << i;
        } else {
            p = trie[p][j];
        }
    }
    return ans;
}

class Solution {
   public:
    vector<int> ans;
    unordered_map<int, vector<pair<int, int>>> m;
    vector<vector<int>> e;
    int root;
    void dfs(int cur) {
        insert(cur, 1);
        for (auto& p : m[cur]) {
            ans[p.second] = query(p.first);
        }
        for (auto& ch : e[cur]) {
            dfs(ch);
        }
        insert(cur, -1);
        return;
    }
    vector<int> maxGeneticDifference(vector<int>& parents, vector<vector<int>>& queries) {
        memset(trie, 0, sizeof trie);
        tot = 1;
        memset(cnt, 0, sizeof cnt);
        int n = parents.size();
        ans.resize(queries.size(), 0);
        e.resize(n);
        for (int i = 0; i < parents.size(); i++) {
            if (parents[i] == -1) {
                root = i;
            } else {
                e[parents[i]].push_back(i);
            }
        }
        for (int i = 0; i < queries.size(); ++i) {
            m[queries[i][0]].push_back({queries[i][1], i});
        }
        dfs(root);
        return ans;
    }
};
