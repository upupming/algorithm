#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int getMaximumConsecutive(vector<int>& coins) {
        sort(coins.begin(), coins.end());
        int i = 1;
        for (int j = 0; j < coins.size(); j++) {
            // 已经可以够造出 0~i-1，判断加上 coins[j] 能不能构造出 i，如果 coins[j] 都不行的话，coins[j+1] 更不行了
            // cout << i << " " << j << " " << coins[j] << endl;
            if (coins[j] <= i) {
                i += coins[j];
            }
        }
        return i;
    }
};
