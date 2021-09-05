#include <bits/stdc++.h>
using namespace std;
/*
https://leetcode-cn.com/problems/first-day-where-you-have-been-in-all-the-rooms/solution/qian-zhui-he-you-hua-dp-by-endlesscheng-j10b/
nextVisit[i] <= i 是一个很重要的条件，说明要往后走，必须是第奇数次访问
因此回访 nextVisit[i] = j 的时候，对 j 一定是第偶数次访问
*/
const int P = 1e9 + 7;
class Solution {
   public:
    int firstDayBeenInAllRooms(vector<int>& nextVisit) {
        int n = nextVisit.size();
        // sum[i] = f[0] + ... + f[i-1]
        vector<int> sum(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int j = nextVisit[i];
            int tmp = (i - j + 1 + sum[i] - sum[j] + P) % P;
            sum[i + 1] = (sum[i] + tmp) % P;
        }
        // n 次向右移一步的传递, -1 因为步数从 0 开始
        return ((n - 1) + sum[n - 1]) % P;
    }
};
