#include <bits/stdc++.h>
using namespace std;
class Solution {
    int dist(int x, int y, vector<int> a) {
        return abs(x - a[0]) + abs(y - a[1]);
    }

   public:
    int nearestValidPoint(int x, int y, vector<vector<int>>& points) {
        int n = points.size();
        int md = INT_MAX, idx = -1;
        for (int i = 0; i < n; i++) {
            if (points[i][0] == x || points[i][1] == y) {
                int d = dist(x, y, points[i]);
                if (d < md) {
                    md = d;
                    idx = i;
                }
            }
        }
        return idx;
    }
};
