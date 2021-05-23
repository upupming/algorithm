#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    vector<int> dist;
    double hour;
    int n;
    bool valid(int mid) {
        double time = 0;
        for (int i = 0; i < n - 1; i++) {
            time += ceil((double)dist[i] / mid);
        }
        time += (double)dist[n - 1] / mid;
        return time <= hour;
    }
    int minSpeedOnTime(vector<int>& _dist, double _hour) {
        dist = _dist;
        hour = _hour;
        n = dist.size();

        int l = 1, r = 1e7;
        if (!valid(r)) return -1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (valid(mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
};
