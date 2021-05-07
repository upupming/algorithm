#include <bits/stdc++.h>
using namespace std;
/*
0. 首先要将 interval 按照左端点从小到大排序，这样考虑每个 query 的时候，interval 的入堆过程是单调的
1. 从小到大考虑每个 query, interval 按照一个右端点的排序用一个优先队列存储，一定是先删除优先队列中最小的一些 interval，再在后部加一些 interval，类似「单调队列」
2. 需要快速获取到最小的区间，因此当区间的右端点相同时，应该按照区间长度排序
*/
struct P {
    int left, right;
    int len() const { return right - left + 1; }
    bool operator<(const P& b) const {
        // right 相等时，left 越大越好，这样区间长度越小
        if (right == b.right) return left < b.left;
        return right > b.right;
    }
};
class Solution {
   public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        int n = intervals.size(), m = queries.size();

        vector<vector<int>> qi(m);
        for (int i = 0; i < m; i++) {
            qi[i].push_back(queries[i]);
            qi[i].push_back(i);
        }

        const auto& cmp = [](auto& a, auto& b) {
            return a[0] < b[0];
        };
        sort(intervals.begin(), intervals.end(), cmp);
        sort(qi.begin(), qi.end(), cmp);

        priority_queue<P> pq;
        multiset<int> s;
        vector<int> ans(m, -1);
        for (int i = 0, j = 0; i < m; i++) {
            while (j < n && intervals[j][0] <= qi[i][0]) {
                P p{intervals[j][0], intervals[j][1]};
                pq.push(p);
                s.insert(p.len());
                j++;
            }
            while (pq.size() && pq.top().right < qi[i][0]) s.erase(s.lower_bound(pq.top().len())), pq.pop();
            if (!pq.size()) continue;

            ans[qi[i][1]] = *s.begin();
        }
        return ans;
    }
};
