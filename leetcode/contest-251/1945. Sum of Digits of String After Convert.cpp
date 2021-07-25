#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int getLucky(string s, int k) {
        string t;
        for (auto& ch : s) {
            t += to_string((ch - 'a' + 1));
        }
        while (k--) {
            int x = 0;
            for (int i = 0; i < t.size(); i++) {
                x += t[i] - '0';
            }
            t = to_string(x);
        }
        return stoi(t);
    }
};
