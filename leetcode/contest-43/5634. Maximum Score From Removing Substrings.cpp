#include <bits/stdc++.h>
using namespace std;
// 贪心。更大先取出结合
class Solution {
   public:
    int maximumGain(string s, int x, int y) {
        int ans = 0;
        int n = s.length();
        if (x < y) {
            swap(x, y);
            for (int i = 0; i < n; i++) {
                if (s[i] == 'a')
                    s[i] = 'b';
                else if (s[i] == 'b')
                    s[i] = 'a';
            }
        }
        // 默认 x > y
        stack<char> stk;
        for (int i = 0; i < n; i++) {
            if (stk.size() && stk.top() == 'a' && s[i] == 'b') {
                ans += x;
                stk.pop();
            } else {
                stk.push(s[i]);
            }
        }
        s = "";
        while (stk.size()) {
            s += stk.top();
            stk.pop();
        }
        n = s.length();
        for (int i = 0; i < n; i++) {
            if (stk.size() && stk.top() == 'a' && s[i] == 'b') {
                ans += y;
                stk.pop();
            } else {
                stk.push(s[i]);
            }
        }
        return ans;
    }
};