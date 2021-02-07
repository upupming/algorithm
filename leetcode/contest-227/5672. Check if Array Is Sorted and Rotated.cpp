#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool check(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            bool sorted = true;
            for (int j = 0; j < n - 1; j++) {
                if (nums[(i + j) % n] > nums[(i + j + 1) % n]) {
                    sorted = false;
                    break;
                }
            }
            if (sorted) return true;
        }
        return false;
    }
};