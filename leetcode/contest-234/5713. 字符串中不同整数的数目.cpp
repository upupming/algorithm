#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    string calc(string t) {
        string u;
        for (int i = 0; i < t.size(); i++) {
            if (t[i] == '0' && u == "") continue;
            u += t[i];
        }
        if (t.size() && u == "") u = "0";
        return u;
    }
    int numDifferentIntegers(string w) {
        unordered_set<string> s;
        bool flag = false;
        string t;
        for (int i = 0; i < w.length(); i++) {
            if (isdigit(w[i]) && !flag) {
                t += w[i];
                flag = true;
            } else if (isdigit(w[i])) {
                t += w[i];
            } else if (!isdigit(w[i])) {
                if (flag) {
                    s.insert(calc(t));
                    t = "";
                }
                flag = false;
            }
        }
        if (flag) {
            s.insert(calc(t));
            t = "";
        }
        return s.size();
    }
};
