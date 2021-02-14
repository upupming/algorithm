#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int calc(string s, int f) {
        int ans = 0;
        for (int i = 0; i < s.length(); i++) {
            char d = (f + i) % 2 + '0';
            if (s[i] != d) ans++;
        }
        return ans;
    }
    int minOperations(string s) {
        return min(calc(s, 0), calc(s, 1));
    }
};