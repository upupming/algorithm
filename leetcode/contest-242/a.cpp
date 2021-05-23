#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool checkZeroOnes(string s) {
        int n = s.length();
        int len0 = 0, len1 = 0;
        for (int i = 0; i < n; i++) {
            int x0 = 0, x1 = 0;
            int j = i;
            while (j < n && s[j] == s[i]) j++;
            if (s[i] == '0')
                x0 = j - i;
            else
                x1 = j - i;
            len0 = max(len0, x0);
            len1 = max(len1, x1);
        }
        return len1 > len0;
    }
};
