#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    string largestMerge(string w1, string w2) {
        int n = w1.size(), m = w2.size();
        string ans;
        for (int i = 0, j = 0; i < n || j < m;) {
            if (i >= n)
                ans += w2[j++];
            else if (j >= m)
                ans += w1[i++];
            else {
                if (w1[i] > w2[j]) {
                    ans += w1[i++];
                } else if (w1[i] < w2[j]) {
                    ans += w2[j++];
                } else {
                    int a = i, b = j;
                    while (a < n && b < m && w1[a] == w2[b]) a++, b++;
                    if (a < n && b < m) {
                        // 这里可以继续优化，直接把这个子串赋值给 ans
                        if (w1[a] > w2[b]) {
                            ans += w1[i++];
                        } else {
                            ans += w2[j++];
                        }
                    } else {
                        if (a < n)
                            ans += w1[i++];
                        else if (b < m)
                            ans += w2[j++];
                        else
                            ans += w1[i++];
                    }
                }
            }
        }
        return ans;
    }
};