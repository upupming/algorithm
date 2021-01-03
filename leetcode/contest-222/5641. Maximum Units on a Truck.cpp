#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        typedef pair<int, int> PII;
        vector<PII> v;
        for (int i = 0; i < boxTypes.size(); ++i) {
            v.emplace_back(boxTypes[i][1], boxTypes[i][0]);
        }
        sort(v.begin(), v.end(), greater<PII>());
        int ans = 0;
        for (int i = 0; i < v.size() && truckSize > 0; ++i) {
            if (truckSize >= v[i].second) {
                ans += v[i].first * v[i].second;
                truckSize -= v[i].second;
            } else {
                ans += v[i].first * truckSize;
                truckSize = 0;
            }
        }
        return ans;
    }
};