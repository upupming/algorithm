/*
 * @lc app=leetcode id=6 lang=cpp
 *
 * [6] ZigZag Conversion
 */

#include <iostream>
#include <string>
using namespace std;

// @lc code=start
class Solution {
   public:
    string convert(string s, int numRows) {
        char m[1010][1010] = {0};
        int maxJ = 0;

        int delta_i = 1, delta_j = 0;
        int i = -1, j = 0;
        for (char ch : s) {
            i += delta_i;
            j += delta_j;
            i = max(0, i);
            i = min(i, numRows - 1);
            m[i][j] = ch;
            maxJ = max(maxJ, j);

            // Case 1: arrived bottom
            if (i == numRows - 1) {
                delta_i = -1;
                delta_j = 1;
            }
            // Case 2: arrived top-right
            else if (i == 0) {
                delta_i = 1;
                delta_j = 0;
            }
        }

        string ans;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j <= maxJ; j++) {
                if (m[i][j]) ans += m[i][j];
            }
        }

        return ans;
    }
};
// @lc code=end
