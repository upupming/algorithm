#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    string maximumNumber(string num, vector<int>& change) {
        string ans;
        int flag = 0;
        for (int i = 0; i < num.size(); i++) {
            auto cur = num[i] - '0';
            auto cur_change = change[cur];
            if (flag == 0) {
                if (cur_change > cur) {
                    ans += cur_change + '0';
                    flag = 1;
                } else {
                    ans += cur + '0';
                }
            } else if (flag == 1) {
                if (cur_change >= cur) {
                    ans += cur_change + '0';
                } else {
                    ans += cur + '0';
                    flag = 2;
                }
            } else {
                ans += cur + '0';
            }
        }
        return ans;
    }
};
