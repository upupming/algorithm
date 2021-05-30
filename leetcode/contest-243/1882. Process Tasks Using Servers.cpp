#include <bits/stdc++.h>
using namespace std;
class Solution {
    struct P {
        int time, idx;
        const bool operator<(const P& b) const {
            return time > b.time;
        }
    };
    struct Q {
        int weight, idx, time;
        const bool operator<(const Q& b) const {
            if (weight == b.weight) {
                return idx > b.idx;
            }
            return weight > b.weight;
        }
    };

   public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size(), m = tasks.size();
        vector<int> ans(m);

        priority_queue<P> p;
        priority_queue<Q> q;
        for (int i = 0; i < n; i++) {
            p.push({0, i});
        }
        int i = 0, time = 0;
        while (i < m) {
            // 出堆一个
            auto now = p.top();
            q.push({servers[now.idx], now.idx, now.time});
            p.pop();
            // cout << now.time << " " << now.idx << endl;
            // 出堆时间相同的全部取出
            while (p.size() && p.top().time == now.time) {
                now = p.top();
                cout << now.idx << endl;
                q.push({servers[now.idx], now.idx, now.time});
                p.pop();
            }
            time = now.time;

            while (q.size() && i < m) {
                if (p.size() && p.top().time <= i) {
                    // 出堆一个
                    auto now = p.top();
                    q.push({servers[now.idx], now.idx, now.time});
                    p.pop();
                    // cout << now.time << " " << now.idx << endl;
                    // 出堆时间相同的全部取出
                    while (p.size() && p.top().time == now.time) {
                        now = p.top();
                        cout << now.idx << endl;
                        q.push({servers[now.idx], now.idx, now.time});
                        p.pop();
                    }
                    time = now.time;
                }
                time = max(time, i);

                auto s = q.top();
                q.pop();
                p.push({time + tasks[i], s.idx});
                // cout << "i: " << i << " " << s.idx << " " << s.weight << " " << s.time << endl;
                ans[i++] = s.idx;
            }
        }

        return ans;
    }
};
