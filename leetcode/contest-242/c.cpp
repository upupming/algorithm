#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.length();
        deque<int> q;
        q.push_back(0);
        for (int i = 1; i < n; i++) {
            while (q.size() && i - q.front() > maxJump) q.pop_front();
            if (q.size() && s[i] == '0' && i - q.front() >= minJump) q.push_back(i);
        }
        return q.back() == n - 1;
    }
};
