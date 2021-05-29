#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int countGoodSubstrings(string s) {
        int ans = 0;
        for (int i = 0; i < s.length(); i++) {
            string t = s.substr(i, 3);
            set<char> st;
            for (auto ch : t) {
                st.insert(ch);
            }
            if (st.size() == 3) ans++;
        }
        return ans;
    }
};
