#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int maximumScore(int a, int b, int c) {
        priority_queue<int, vector<int>> pq;
        pq.push(a), pq.push(b), pq.push(c);
        int ans = 0;
        while (true) {
            int x = pq.top();
            pq.pop();
            int y = pq.top();
            pq.pop();
            if (x == 0 || y == 0) break;
            ans += 1;
            pq.push(x - 1), pq.push(y - 1);
        }
        return ans;
    }
};