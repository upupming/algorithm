#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool sumGame(string num) {
        int n = num.size();
        int s1 = 0, s2 = 0, c1 = 0, c2 = 0;

        for (int i = 0; i < n / 2; i++) {
            if (num[i] == '?')
                c1++;
            else
                s1 += num[i] - '0';
        }
        for (int i = n / 2; i < n; i++) {
            if (num[i] == '?')
                c2++;
            else
                s2 += num[i] - '0';
        }
        // 两边都有的问号可以消去
        if (c1 > c2)
            c1 -= c2, c2 = 0;
        else
            c2 -= c1, c1 = 0;
        // 对称性，不妨假设 c1 == 0
        if (c2 == 0) {
            swap(c1, c2);
            swap(s1, s2);
        }
        if (c1 == 0) {
            // 不管 Bob 填多小的数，都有 s2 > s1
            if (s1 < s2 + 9 * ((c2 + 1) / 2) + 0 * (c2 / 2)) return true;
            // 不管 Bob 填多大的数，都有 s2 < s1
            if (s1 > s2 + 0 * ((c2 + 1) / 2) + 9 * (c2 / 2)) return true;
        }
        return false;
    }
};
