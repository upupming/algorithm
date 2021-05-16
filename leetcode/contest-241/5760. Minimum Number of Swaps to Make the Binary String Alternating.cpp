#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int cntNum(string &s, int x) {
        int ans = 0;
        for (auto ch : s) {
            if (ch - '0' == x) ans++;
        }
        return ans;
    }
    int cntSwap(string &s, string &t) {
        // cout << s << " " << t << endl;
        int n = s.length();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] != t[i]) {
                ans++;
            }
        }
        return ans / 2;
    }
    int minSwaps(string s) {
        int n = s.length();
        int c0 = cntNum(s, 0), c1 = cntNum(s, 1);
        if (abs(c0 - c1) >= 2) return -1;
        string s0, s1;
        for (int i = 0; i < c0 && i < c1; i++) {
            s0 += "01";
            s1 += "10";
        }
        for (int i = min(c0, c1); i < c0; i++) {
            s0 += "0";
        }
        for (int i = min(c0, c1); i < c1; i++) {
            s1 += "1";
        }
        int ans = INT_MAX;
        if (s0.length() == n) ans = min(ans, cntSwap(s, s0));
        if (s1.length() == n) ans = min(ans, cntSwap(s, s1));
        return ans;
    }
};
