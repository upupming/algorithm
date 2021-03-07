#include <bits/stdc++.h>
using namespace std;
/*
符合条件的点对数目 = 总点对数目 - 不符合条件的点对数目

点对 (i, j) 的可连边数 = deg[i] + deg[j] - cnt[i][j]，其中 cnt[i][j] 表示i 和 j 直接相连的边数

首先将所有的点按照度 deg 从小到大排列，应用双指针算法

*/
const int N = 2e5 + 10;
unordered_map<int, unordered_map<int, int>> w;
int a[N];
int cal(int x, int y) {
    return 3 * 1e4 * x + y;
}
class Solution {
   public:
    vector<int> countPairs(int n, vector<vector<int>>& e, vector<int>& q) {
        const int m = e.size();
        // deg 和 c 一样，但是 c 后面会排序一下
        vector<int> deg(n + 1, 0), c(n + 1, 0);
        for (const auto& eg : e) {
            int x = eg[0], y = eg[1];
            deg[x]++, deg[y]++;
            c[x]++, c[y]++;
        }
        sort(c.begin(), c.end());

        for (int i = 0; i < e.size(); i++) {
            // 确保 e[i][0] < e[i][1]
            if (e[i][0] > e[i][1]) {
                swap(e[i][0], e[i][1]);
            }
        }
        sort(e.begin(), e.end());

        vector<int> ans;
        for (int q : q) {
            int res = n * (n - 1) / 2;
            int l = 1, r = n;
            while (l < r) {
                // l 和 r 都不可能满足，那么 l 和 [l+1, r] 里面的都不能满足
                if (c[l] + c[r] <= q) {
                    res -= r - l;
                    l++;
                } else {
                    // l 和 r 可以满足，那么看看和 r-1 能不能满足
                    r--;
                }
            }

            int dup = 1;
            for (int i = 0; i < m; i++) {
                // 巧妙地利用了 vector 的排序来将重边放在相邻的位置
                // 这样直接分析当前和下一个就知道是不是重边了
                if (i < m - 1 && e[i] == e[i + 1]) {
                    dup++;
                    continue;
                }
                int x = e[i][0], y = e[i][1];
                // 如果 d(x) + d(y) > q 且 d(x) + d(y) - dup <= q，则说明这个数对应当额外被排除
                if (deg[x] + deg[y] > q && deg[x] + deg[y] - dup <= q) {
                    res--;
                }
                dup = 1;
            }
            ans.push_back(res);
        }

        return ans;
    }
};
