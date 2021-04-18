#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        vector<int> ans;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        map<int, vector<int>> mp;
        int n = tasks.size();
        for (int i = 0; i < n; ++i)
            mp[tasks[i][0]].emplace_back(i);
        int now = 0;

        for (auto [t, v] : mp) {
            while (now < t && !pq.empty()) {
                auto [duration, idx] = pq.top();
                pq.pop();
                ans.emplace_back(idx);
                now += duration;
            }
            if (now < t && pq.empty()) {
                now = t;
            }
            if (now >= t) {
                for (int i : v)
                    pq.emplace(tasks[i][1], i);
            }
        }

        // Remaining tasks
        while (!pq.empty()) {
            ans.emplace_back(pq.top().second);
            pq.pop();
        }

        return ans;
    }
};
