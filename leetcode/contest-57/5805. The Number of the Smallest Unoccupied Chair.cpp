#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    struct P {
        int a, l, idx, seat;
        bool operator<(const P& rhs) const {
            return l > rhs.l;
        }
    };
    priority_queue<P> pq;
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        int n = times.size();
        set<int> s;
        for (int i = 0; i < n; ++i) {
            s.insert(i);
        }
        for (int i = 0; i < n; ++i) {
            times[i].push_back(i);
        }
        sort(times.begin(), times.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0];
        });

        for (auto& t : times) {
            // cout << t[0] << " " << t[1] << " " << t[2] << endl;
            while (pq.size() && pq.top().l <= t[0]) {
                s.insert(pq.top().seat);
                pq.pop();
            }
            pq.push(P{t[0], t[1], t[2], *s.begin()});
            if (t[2] == targetFriend) {
                return *s.begin();
            }
            s.erase(s.begin());
        }
        return -1;
    }
};
