#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
struct Node {
    int u, v, dis, idx;
    bool operator<(const Node& b) {
        return dis < b.dis;
    }
} e[N], q[N];

class Solution {
    vector<int> parent;
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

   public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        int m = edgeList.size(), k = queries.size();
        for (int i = 0; i < m; i++)
            e[i] = {edgeList[i][0], edgeList[i][1], edgeList[i][2]};
        for (int i = 0; i < k; i++)
            q[i] = {queries[i][0], queries[i][1], queries[i][2], i};

        sort(e, e + m);
        sort(q, q + k);

        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;

        vector<bool> ans(k);
        // 类似双指针，右端点 i 表示查询，左端点 j 表示边
        for (int i = 0, j = 0; i < k; i++) {
            while (j < m && e[j].dis < q[i].dis) {
                int x = find(e[j].u);
                parent[x] = find(e[j].v);
                j++;
            }
            ans[q[i].idx] = (find(q[i].u) == find(q[i].v));
        }

        return ans;
    }
};