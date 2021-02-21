#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    string mergeAlternately(string w1, string w2) {
        int n = w1.length(), m = w2.length();
        string ans;
        for (int i = 0; i < min(m, n); i++) {
            ans += w1[i];
            ans += w2[i];
        }
        // cout << m << " " << n << endl;
        if (m > n)
            ans += w2.substr(n);
        else {
            ans += w1.substr(m);
            // cout << w1.substr(m) << endl;
        }
        return ans;
    }
};
