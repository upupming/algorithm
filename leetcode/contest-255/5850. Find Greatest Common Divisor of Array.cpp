#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int findGCD(vector<int>& nums) {
        int mi = INT_MAX, ma = INT_MIN;
        for (auto& a : nums) {
            mi = min(a, mi);
            ma = max(a, ma);
        }
        return __gcd(mi, ma);
    }
};
