#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int countHomogenous(string s) {
        long long n = s.length(), ans = 0;
        for (int i = 0; i < n;) {
            int j = i + 1;
            while (j < n && s[j] == s[i]) j++;
            // cout << i << j << endl;
            int k = j - i;
            ans = (ans + k * (k + 1ll) / 2) % (int)(1e9 + 7);
            i = j;
        }
        return ans;
    }
};