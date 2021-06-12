#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        vector<int> in(100);
        for (auto& r : ranges) {
            for (int i = r[0]; i <= r[1]; i++) {
                in[i] = 1;
            }
        }
        for (int i = left; i <= right; i++) {
            if (!in[i]) return false;
        }
        return true;
    }
};
