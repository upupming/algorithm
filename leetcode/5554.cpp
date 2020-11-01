// https://leetcode.com/contest/weekly-contest-213/problems/check-array-formation-through-concatenation/

#include <bits/stdc++.h>
using namespace std;
// Input: arr = [91,4,64,78], pieces = [[78],[4,64],[91]]
class Solution {
   public:
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
        for (auto p : pieces) {
            auto i = find(arr.begin(), arr.end(), p[0]) - arr.begin();
            auto j = find(arr.begin(), arr.end(), p[p.size() - 1]) - arr.begin();
            if (i == arr.size() || j == arr.size()) return false;
            if (i > j) return false;
            for (int c = i; c <= j; c++) {
                if (arr[c] != p[c - i]) return false;
            }
        }
        return true;
    }
};