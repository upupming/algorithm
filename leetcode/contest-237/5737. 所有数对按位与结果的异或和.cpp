#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        int sum1 = 0, sum2 = 0;
        for (auto& x : arr1) sum1 ^= x;
        for (auto& x : arr2) sum2 ^= x;
        return sum1 & sum2;
    }
};
