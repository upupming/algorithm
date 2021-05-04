#include <bits/stdc++.h>
using namespace std;
/*
1. 将 queries 按照 limit 从小到大排序，每次处理一个 query 就将小于 limit 的所有的边加入到图中，用并查集维护是否有路的信息即可
2. 因为有重边，所以可以直接忽略权值较大的边（重复 merge 不影响）
*/
class Solution {
    vector<int> fa;
    int get(int x) {
        if (x == fa[x]) return x;
        // 路径压缩，fa 直接赋值为代表元素
        return fa[x] = get(fa[x]);
    }
    void merge(int x, int y) {
        int fx = get(x), fy = get(y);
        if (fx == fy) return;
        fa[fx] = fy;
    }

   public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        int m = queries.size(), l = edgeList.size();
        vector<int> qIdx(m);
        vector<bool> ans(m, false);
        iota(qIdx.begin(), qIdx.end(), 0);
        sort(qIdx.begin(), qIdx.end(), [&queries](auto& a, auto& b) {
            return queries[a][2] < queries[b][2];
        });
        sort(edgeList.begin(), edgeList.end(), [](auto& a, auto& b) {
            return a[2] < b[2];
        });
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);

        for (int i = 0, j = 0; i < m; i++) {
            auto& q = queries[qIdx[i]];
            while (j < l && edgeList[j][2] < q[2]) merge(edgeList[j][0], edgeList[j][1]), j++;
            if (get(q[0]) == get(q[1])) ans[qIdx[i]] = true;
        }
        return ans;
    }
};
