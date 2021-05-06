#include <bits/stdc++.h>
using namespace std;
/*
1. 将 queries 按照 minSize 排序，从大到小考虑每个 query，将 >= minSize 的 room 加入到 set 中，set 中的 room 按照 id 排序
2. 对于每个 query 查询 preferred 两侧最近的两个 id，取 abs(id - preferred) 的最小就是答案
*/
class Solution {
   public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        int n = rooms.size(), m = queries.size();
        for (int i = 0; i < m; i++) {
            queries[i].push_back(i);
        }

        const auto& cmp = [](auto& a, auto& b) {
            return a[1] < b[1];
        };
        sort(rooms.begin(), rooms.end(), cmp);
        sort(queries.begin(), queries.end(), cmp);

        vector<int> ans(m, INT_MAX);
        set<int> ids;
        // 哨兵
        ids.insert(-1e9), ids.insert(1e9);
        for (int i = m - 1, j = n - 1; i >= 0; i--) {
            auto q = queries[i];
            while (j >= 0 && rooms[j][1] >= q[1]) {
                ids.insert(rooms[j][0]);
                j--;
            }

            auto it1 = ids.lower_bound(q[0]);
            if (abs(*it1 - q[0]) < abs(ans[q[2]] - q[0])) {
                ans[q[2]] = *it1;
            }
            it1--;
            // <=, 同等值选 id 更小的
            if (abs(*it1 - q[0]) <= abs(ans[q[2]] - q[0])) {
                ans[q[2]] = *it1;
            }
            if (ans[q[2]] > 1e8) ans[q[2]] = -1;
        }
        return ans;
    }
};
