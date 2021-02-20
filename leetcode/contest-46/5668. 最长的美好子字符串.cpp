#include <bits/stdc++.h>
using namespace std;
class Solution {
    bool is(string s) {
        set<char> st;
        int n = s.length();
        for (int i = 0; i < n; i++) {
            st.insert(s[i]);
        }
        for (auto x : st) {
            if (x >= 'a' && x <= 'z') {
                if (!st.count(x - 'a' + 'A')) return false;
            } else {
                if (!st.count(x - 'A' + 'a')) return false;
            }
        }
        return true;
    }

   public:
    string longestNiceSubstring(string s) {
        string ans;
        int n = s.length();
        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                string t = s.substr(i, len);
                if (is(t)) {
                    ans = t;
                    break;
                }
            }
        }
        return ans;
    }
};
