#include <bits/stdc++.h>
using namespace std;
struct Time {
    int h, m;
    Time(int h, int m) : h(h), m(m) {}
    Time(string s) {
        h = (s[0] - '0') * 10 + s[1] - '0';
        m = (s[3] - '0') * 10 + s[4] - '0';
    }
};
bool cmp(Time s, Time f) {
    if (s.h < f.h) return true;
    if (s.h > f.h) return false;
    if (s.m < f.m) return true;
    return false;
}
int cnt(Time s, Time f) {
    int ans = 0;
    for (int h = s.h; h <= f.h; h++) {
        for (int m = 0; m <= 45; m += 15) {
            Time tmp(h, m);
            if (
                !cmp(tmp, s) && !cmp(f, tmp)) {
                // cout << h << " " << m << endl;
                ans++;
            }
        }
    }
    return max(ans - 1, 0);
}
class Solution {
   public:
    int numberOfRounds(string startTime, string finishTime) {
        Time s(startTime), f(finishTime);
        Time a(23, 59), b(0, 0);
        if (!cmp(f, s)) {
            return cnt(s, f);
        } else {
            f.h += 24;
            return cnt(s, f);
        }
    }
};
