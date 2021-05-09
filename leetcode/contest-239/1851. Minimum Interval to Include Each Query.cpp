#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        int n = intervals.size(), q = queries.size();
        vector<int> ans(q);

        vector<int> order(q);
        for (int i = 0; i < q; ++i)
            order[i] = i;
        // 从小到大考虑查询，保证区间可以有序地增加、删除
        sort(order.begin(), order.end(), [&](int i, int j) {
            return queries[i] < queries[j];
        });

        sort(intervals.begin(), intervals.end());
        // 不断加入可能的区间、删除不可能的区间
        // pair<区间长度, 区间右端点>，因为我们要尽量短的区间长度
        set<pair<int, int>> s;
        int ptr = -1;

        for (int i : order) {
            int qi = queries[i];
            // 左端点在查询左侧，可能包含查询
            while (ptr + 1 < n && intervals[ptr + 1][0] <= qi) {
                ptr++;
                s.emplace(intervals[ptr][1] - intervals[ptr][0] + 1, intervals[ptr][1]);
            }

            // 类似单调队列，删除不再包含 qi 的区间，不包含 qi，一定也不会包含更右边的点
            while (!s.empty() && s.begin()->second < qi)
                s.erase(s.begin());

            if (s.empty())
                ans[i] = -1;
            else
                ans[i] = s.begin()->first;
        }

        return ans;
    }
};
