#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int maximumPopulation(vector<vector<int>>& logs) {
        int ans = -1, maxS = 0;
        for (int i = 1950; i <= 2050; i++) {
            int cnt = 0;
            for (auto& a : logs) {
                if (i >= a[0] && i <= a[1] - 1) {
                    cnt++;
                }
            }
            if (maxS < cnt) {
                ans = i;
                maxS = cnt;
            }
        }
        return ans;
    }
};
