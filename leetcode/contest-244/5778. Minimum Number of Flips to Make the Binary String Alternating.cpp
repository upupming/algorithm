#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
/*
s 长为偶数, 0101...01, 1010...10
s 长为奇数, 0101...010,     1010...101,
         0101...001...01, 1010...110...10,
l[0][i] 表示 s[0~i] 变成以 0 开头的交替串的变化次数
l[1][i] 表示 s[0~i] 变成以 1 开头的交替串的变化次数
r[0][i] 表示 s[i~n-1] 变成以 0 结尾的交替串的变化次数
r[1][i] 表示 s[i~n-1] 变成以 1 结尾的交替串的变化次数
长为偶数，答案就是 min(l[0][n-1], l[1][n-1])
长为奇数，答案就是 min(l[0][i] + r[0][i+1], l[1][i] + l[1][i+1]) for all i, 再  min(l[0][n-1], l[1][n-1])
*/
class Solution {
   public:
    int minFlips(string s) {
        int n = s.length();
        vector<int> l[2], r[2];
        l[0] = l[1] = r[0] = r[1] = vector<int>(n);
        for (int k = 0; k < 2; k++) {
            for (int i = 0, c = k; i < n; i++, c ^= 1) {
                if (s[i] - '0' == c)
                    l[k][i] = i - 1 >= 0 ? l[k][i - 1] : 0;
                else
                    l[k][i] = i - 1 >= 0 ? l[k][i - 1] + 1 : 1;
            }
        }
        for (int k = 0; k < 2; k++) {
            for (int i = n - 1, c = k; i >= 0; i--, c ^= 1) {
                if (s[i] - '0' == c)
                    r[k][i] = i + 1 < n ? r[k][i + 1] : 0;
                else
                    r[k][i] = i + 1 < n ? r[k][i + 1] + 1 : 1;
            }
        }
        int ans = min(l[0][n - 1], l[1][n - 1]);
        if (n % 2 == 0) {
            return ans;
        } else {
            for (int i = 0; i + 1 < n; i++) {
                ans = min(ans, l[0][i] + r[1][i + 1]);
                ans = min(ans, l[1][i] + r[0][i + 1]);
            }
            return ans;
        }
    }
};
