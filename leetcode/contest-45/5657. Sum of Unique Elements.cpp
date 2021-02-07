#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int sumOfUnique(vector<int>& nums) {
        int ans = 0;
        map<int, int> m;
        for (auto a : nums) {
            m[a]++;
        }
        for (auto a : nums) {
            if (m[a] == 1) ans += a;
        }
        return ans;
    }
};