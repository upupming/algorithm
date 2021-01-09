#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int totalMoney(int n) {
        int ans = 0;
        for (int i = 0, j = 1; i < n; i++) {
            ans += i % 7 + j;
            if ((i + 1) % 7 == 0) j++;
        }
        return ans;
    }
};