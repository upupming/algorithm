#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<int> memLeak(int memory1, int memory2) {
        priority_queue<pair<int, int>> q;
        q.push({memory1, 1}), q.push({memory2, 0});
        for (int i = 1;; i++) {
            if (q.top().first < i) {
                int a[2];
                while (q.size()) {
                    auto now = q.top();
                    a[now.second] = now.first;
                    q.pop();
                }
                return {i, a[1], a[0]};
            }
            auto now = q.top();
            now.first -= i;
            q.pop();
            q.push(now);
        }
        return {-1, -1, -1};
    }
};
