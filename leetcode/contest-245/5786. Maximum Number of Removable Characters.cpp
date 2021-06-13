#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    string s, p;
    vector<int> re;
    unordered_map<int, int> re2Idx;
    bool valid(int mid) {
        int i = 0, j = 0;
        for (; i < s.length(); i++) {
            if (re2Idx.count(i) && re2Idx[i] < mid) continue;
            if (s[i] == p[j]) {
                j++;
            }
        }
        return j == p.size();
    }
    int maximumRemovals(string _s, string _p, vector<int>& _re) {
        s = _s, p = _p, re = _re;
        int l = 0, r = re.size();
        for (int i = 0; i < re.size(); i++) {
            re2Idx[re[i]] = i;
        }
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (valid(mid))
                l = mid;
            else
                r = mid - 1;
        }
        return l;
    }
};
