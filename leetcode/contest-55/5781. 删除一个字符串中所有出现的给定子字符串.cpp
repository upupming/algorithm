#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int N = 1e3 + 10;
const int P = 131;

ULL f[N], p[N];
bool st[N];
class Solution {
   public:
    ULL pt = 0, len;
    string removeOccurrences(string s, string part) {
        int n = s.length();
        len = part.length();
        p[0] = 1;
        for (int i = 1; i <= n; i++) {
            p[i] = p[i - 1] * 131;
        }
        for (int i = 1; i <= len; i++) {
            pt = pt * P + (part[i - 1] - 'a' + 1);
            // cout << "i:" << i << " " << pt << endl;
        }
        bool flag = false;
        while (!flag) {
            // cout << s << endl;
            n = s.length();
            for (int i = 1; i <= n; i++) {
                st[i] = 1;
            }
            bool flag = false;
            int n = s.length();
            for (int i = 1; i <= n; i++) {
                f[i] = f[i - 1] * P + (s[i - 1] - 'a' + 1);
                // cout << i << " " << f[i] << endl;
            }
            // [i, i+len-1]
            for (int i = 1; i + len - 1 <= n; i++) {
                int l = i, r = i + len - 1;
                // cout << l << " " << r << " " << f[r] - f[l - 1] * p[r - l + 1] << endl;
                if (f[r] - f[l - 1] * p[r - l + 1] == pt) {
                    flag = true;
                    for (int j = l; j <= r; j++) {
                        st[j] = 0;
                    }
                    i = r;
                }
            }
            if (!flag) break;
            string t;
            for (int i = 1; i <= n; i++) {
                if (st[i])
                    t += s[i - 1];
            }
            s = t;
        }
        return s;
    }
};
