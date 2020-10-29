// https://leetcode.com/contest/weekly-contest-212/problems/slowest-key/
#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        vector<bool> res;

        for (int i = 0; i < l.size(); i++) {
            vector<int> tmp(nums.begin() + l[i], nums.begin() + r[i] + 1);
            sort(tmp.begin(), tmp.end());
            bool ok = true;
            for (auto it = tmp.begin() + 1; it != tmp.end() - 1; it++) {
                if (*(it + 1) - *it != *it - *(it - 1)) {
                    ok = false;
                    break;
                }
            }
            res.push_back(ok);
        }

        return res;
    }
};