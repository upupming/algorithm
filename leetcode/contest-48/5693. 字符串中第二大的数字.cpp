#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int secondHighest(string s) {
        set<int> st;
        for (auto& c : s) {
            if (isdigit(c)) st.insert(c - '0');
        }
        if (st.size() <= 1) return -1;
        auto it = st.end();
        it--, it--;
        return *it;
    }
};
