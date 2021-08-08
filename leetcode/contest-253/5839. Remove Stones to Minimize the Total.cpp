#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int minStoneSum(vector<int>& piles, int k) {
        priority_queue<int> q;
        int ans = 0;
        for (auto& p : piles) {
            q.push(p);
            ans += p;
        }
        while (k--) {
            auto t = q.top();
            q.pop();
            int a = t / 2, b = t - a;
            ans -= a;
            q.push(b);
        }
        return ans;
    }
};
