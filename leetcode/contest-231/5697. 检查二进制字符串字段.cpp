#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    bool checkOnesSegment(string s) {
        int flag = 1;
        int n = s.length();
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                if (flag == 2) flag = 3;
                continue;
            }
            if (flag == 1)
                flag = 2;
            else if (flag == 3)
                return false;
        }
        return true;
    }
};
