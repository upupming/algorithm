#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> m;
        for (auto& p : knowledge) {
            m[p[0]] = p[1];
        }
        string t, cur;
        bool flag = false;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(')
                flag = true;
            else if (s[i] == ')') {
                if (m.count(cur))
                    t += m[cur];
                else
                    t += '?';
                cur = "";
                flag = false;
            } else {
                if (flag)
                    cur += s[i];
                else
                    t += s[i];
            }
        }
        return t;
    }
};
