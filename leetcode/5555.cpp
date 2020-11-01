// https://leetcode.com/contest/weekly-contest-213/problems/count-sorted-vowel-strings/

#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    // cur: 5, 4, 3, 2, 1; cur - 1 for used char
    int dfs(int depth, int cur, int n) {
        if (depth == n - 1) return cur;

        int ans = 0;
        // Choice for current char
        for (int i = 1; i <= cur; i++) {
            ans += dfs(depth + 1, i, n);
        }

        return ans;
    }
    int countVowelStrings(int n) {
        return dfs(0, 5, n);
    }
};