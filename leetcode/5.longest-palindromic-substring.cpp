/*
 * @lc app=leetcode id=5 lang=cpp
 *
 * [5] Longest Palindromic Substring
 */

#include <string>
using namespace std;
// @lc code=start
class Solution {
public:

    string longestPalindrome(string s) {
        return longestPalindromeDP(s);
    }
    string longestPalindromeDP(string s) {
        int n = s.length(), maxLength = 0;
        string ans;
        // if [s[i]...s[j]] is palindromic
        bool dp[n][n];
        // Initialize
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
            if (1 > maxLength) {
                maxLength = 1;
                ans = s.substr(i, 1);
            }
            if (i < n - 1) {
                dp[i][i+1] = (s[i] == s[i+1]);
                if (dp[i][i+1] && 2 > maxLength) {
                    maxLength = 2;
                    ans = s.substr(i, 2);
                }
            }
        }
        // dp along the diagonal
        for (int diff = 2; diff < n; diff++) {
            for (int b = 0; b < n - diff; b++) {
                dp[b][b + diff] = (s[b] == s[b+diff]) ? dp[b+1][b+diff-1] : false;
                if (dp[b][b + diff]) {
                    if (diff + 1 > maxLength) {
                        maxLength = diff + 1;
                        ans = s.substr(b, diff + 1);
                    }
                }
            }
        }

        return ans;
    }
    string longestPalindromeExpand(string s) {
        int n = s.length();
        string ans = "";
        for (int i = 0; i < n; i++) {
            int len1 = expand(s, i, i+1), len2 = 0;
            if (i < n-1 && s[i] == s[i+1]) {
                len2 = expand(s, i, i+2);
            }
            int len = max(len1, len2);
            if (len > ans.length()) {
                ans = s.substr(
                    (i - len - 1) / 2,
                    len
                );
            }
        }
        return ans;
    }
    int expand(string s, int start, int end) {
        int L = start, R = end;
        while (L > 0 && R < s.length() && s[L-1] == s[R]) {
            L--;
            R++;
        }
        return R - L;
    }
};
// @lc code=end

