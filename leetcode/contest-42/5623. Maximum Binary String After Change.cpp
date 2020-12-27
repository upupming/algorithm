#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    string maximumBinaryString(string s) {
        // 看第 1 个 0 后面有多少 0，就向后移动几位即可，最后的结果一定只有一个 0
        int n = s.length();
        int k = 0, cnt = 0;
        while (s[k] == '1' && k < n) k++;
        // 全 1，直接返回
        if (k == n) return s;
        // 找到后面的 0 的个数
        for (int i = k + 1; i < n; i++) {
            cnt += s[i] == '0';
        }
        string ans(n, '1');
        ans[k + cnt] = '0';
        return ans;
    }
};