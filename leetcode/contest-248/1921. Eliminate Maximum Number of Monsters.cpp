#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        int n = dist.size();
        vector<double> t;
        for (int i = 0; i < n; i++) {
            t.push_back((double)dist[i] / speed[i]);
        }
        sort(t.begin(), t.end());
        for (int i = 0; i < n; i++) {
            if (t[i] <= i) return i;
        }
        return n;
    }
};
