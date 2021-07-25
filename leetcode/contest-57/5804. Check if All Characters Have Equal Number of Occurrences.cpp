#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool areOccurrencesEqual(string s) {
        unordered_map<char, int> m;
        for (auto ch : s) {
            m[ch]++;
        }
        int x = -1;
        for (auto &[a, b] : m) {
            if (x == -1) {
                x = b;
            } else {
                if (b != x) return false;
            }
        }
        return true;
    }
};
