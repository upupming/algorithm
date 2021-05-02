#include <bits/stdc++.h>
using namespace std;
struct P {
    int size, id;
    bool operator<(const struct P& b) const {
        if (size == b.size) return id < b.id;
        return size < b.size;
    }
};
struct Q {
    int minSize, prefferred, idx;
    bool operator<(const struct Q& b) const {
        // 本来只需要按照 minSize 排序即可
        // 但是需要防止 set 认为 minSize 相同就是同一个元素
        if (minSize == b.minSize) {
            if (prefferred == b.prefferred) {
                return idx < b.idx;
            }
            return prefferred < b.prefferred;
        }
        return minSize < b.minSize;
    }
};
class Solution {
   public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        int n = rooms.size(), k = queries.size();
        vector<int> ans(k, -1);
        set<P> s;
        set<int> t;
        for (auto& room : rooms) {
            s.insert({room[1], room[0]});
        }
        set<Q> qrs;
        for (int i = 0; i < k; i++) {
            auto& q = queries[i];
            qrs.insert({q[1], q[0], i});
        }
        // cout << k << " " << qrs.size() << endl;
        auto it1 = s.rbegin();
        // 从大到小考虑每个查询
        for (auto it = qrs.rbegin(); it != qrs.rend(); it++) {
            // cout << it->idx << endl;
            while (it1 != s.rend() && it1->size >= it->minSize) t.insert(it1->id), it1++;
            if (!t.size()) continue;
            auto it2 = t.lower_bound({it->prefferred});
            auto it3 = it2;
            it3--;
            auto cd = t.begin();
            if (it2 == t.end()) {
                // cout << "it3->id:" << *it3 << endl;
                cd = it3;
            } else if (it2 == t.begin()) {
                // cout << "it2->id:" << *it2 << endl;
                cd = it2;
            } else {
                // cout << *it2 << " " << *it3 << endl;
                if (abs(*it2 - it->prefferred) < abs(*it3 - it->prefferred)) {
                    cd = it2;
                } else {
                    cd = it3;
                }
            }
            ans[it->idx] = *cd;
        }

        return ans;
    }
};
