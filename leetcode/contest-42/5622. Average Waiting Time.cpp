#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    double averageWaitingTime(vector<vector<int>>& cus) {
        long long lastEndTime = 1, tot = 0;
        for (int i = 0; i < cus.size(); i++) {
            long long wait = max(lastEndTime - cus[i][0], 0ll) + cus[i][1];
            tot += wait;
            lastEndTime = max(lastEndTime, cus[i][0] + wait);
        }
        return tot / 1.0 / cus.size();
    }
};