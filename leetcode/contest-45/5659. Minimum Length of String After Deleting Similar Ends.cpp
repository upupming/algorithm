#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int minimumLength(string s) {
        deque<char> dq;
        for (int i = 0; i < s.length(); i++) {
            dq.push_back(s[i]);
        }
        while (dq.size() >= 2 && dq.front() == dq.back()) {
            char ch = dq.front();
            while (dq.size() && dq.front() == ch) dq.pop_front();
            while (dq.size() && dq.back() == ch) dq.pop_back();
        }
        return dq.size();
    }
};