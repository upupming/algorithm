#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int numberOfMatches(int n) {
        int ans = 0;
        while (n > 1) {
            ans += n / 2;
            n = ceil(n / 2.0);
        }
        return ans;
    }
};