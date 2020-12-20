#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    string reformatNumber(string number) {
        int n = number.length();
        string t, ans;
        for (int i = 0; i < n; i++) {
            if (number[i] == '-' || number[i] == ' ') continue;
            t += number[i];
        }
        int m = t.length(), g = m / 3, r = m % 3;
        if (r == 1) g--, r += 3;
        for (int i = 0; i < g; i++) {
            if (i > 0)
                ans += '-';
            ans += t.substr(3 * i, 3);
        }
        if (r == 2)
            ans += (g > 0 ? "-" : "") + t.substr(m - r, 2);
        else if (r == 4)
            ans += (g > 0 ? "-" : "") + t.substr(m - 4, 2) + '-' + t.substr(m - 2, 2);
        return ans;
    }
};