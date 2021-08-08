#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int minSwaps(string s) {
        int n = s.length();
        stack<int> t;
        t.push(0);
        int j = n - 1;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == ']' && t.top() == 0) {
                while (s[j] == '[') j--;
                s[j] = ']';
                t.push(1);
                ans++;
            } else {
                if (s[i] == '[')
                    t.push(t.top() + 1);
                else
                    t.push(t.top() - 1);
            }
        }
        return ans;
    }
};
