#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int eatenApples(vector<int>& a, vector<int>& d) {
        int n = a.size();
        typedef pair<int, int> PII;
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        int ans = 0;
        for (int i = 1;; i++) {
            if (i <= n) {
                pq.emplace(i + d[i - 1], a[i - 1]);
            }
            // 把所有过期的全部取出
            while (pq.size() && pq.top().first <= i) pq.pop();
            if (pq.empty() && i <= n) continue;
            if (pq.empty()) break;
            // 吃一个堆顶的苹果
            ans++;
            auto top = pq.top();
            pq.pop();
            top.second--;
            if (top.second > 0) pq.push(top);
            // cout << i << " " << top.first << " " << top.second << endl;
            // cout << pq.size() << endl;
        }
        return ans;
    }
};