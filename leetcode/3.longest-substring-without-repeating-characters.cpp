/*
 * @lc app=leetcode id=3 lang=cpp
 *
 * [3] Longest Substring Without Repeating Characters
 */

#include <set>
#include <map>
#include <string>
using namespace std;

// @lc code=start
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        return lengthOfLongestSubstringMap(s);
    }
    // O(2n)
    int lengthOfLongestSubstringSet(string s) {
        int n = s.length();
        int i = 0, j = 0, ans = 0;
        set<char> chars;
        while (i < n && j < n) {
            if (chars.count(s[j])) {
                chars.erase(s[i++]);
            } else {
                chars.insert(s[j++]);
                ans = max(ans, j - i);
            }
        }
        return ans;
    }
    // O(n)
    int lengthOfLongestSubstringMap(string s) {
        int n = s.length();
        int i = 0, j = 0, ans = 0;
        map<char, int> chars2Index;
        while (i < n && j < n) {
            if (chars2Index.count(s[j]) && chars2Index[s[j]] >= i) {
                i = chars2Index[s[j]] + 1;
                chars2Index.erase(s[j]);
            } else {
                chars2Index[s[j++]] = j;
                ans = max(ans, j - i);
            }
        }
        return ans;
    }
};

// @lc code=end

