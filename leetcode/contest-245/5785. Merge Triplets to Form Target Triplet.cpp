#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool mergeTriplets(vector<vector<int>>& s, vector<int>& t) {
        int y0 = INT_MAX, z0 = INT_MAX, x1 = INT_MAX, z1 = INT_MAX, x2 = INT_MAX, y2 = INT_MAX;
        for (auto& a : s) {
            if (a[0] == t[0]) {
                y0 = min(y0, a[1]);
                z0 = min(z0, a[2]);
            }
            if (a[1] == t[1]) {
                x1 = min(x1, a[0]);
                z1 = min(z1, a[2]);
            }
            if (a[2] == t[2]) {
                x2 = min(x2, a[0]);
                y2 = min(y2, a[1]);
            }
        }
        return x1 <= t[0] && x2 <= t[0] && y0 <= t[1] && y2 <= t[1] && z0 <= t[2] && z1 <= t[2];
    }
};
