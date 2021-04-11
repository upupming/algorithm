#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int minSideJumps(vector<int>& o) {
        int n = o.size() - 1;

        vector<vector<int>> seen(4, vector<int>(n + 1));
        for (int j = 1; j <= 3; j++) {
            for (int i = n - 1; i >= 0; i--) {
                if (o[i] == 0 || o[i] == j)
                    seen[j][i] = seen[j][i + 1];
                else
                    seen[j][i] = o[i];
            }
        }

        int ans = 0;
        int cur = 2;
        for (int i = 1; i <= n - 1; i++) {
            // 将要走到 i，但是 i 挡住了的话
            if (o[i] == cur) {
                if (cur == 2) {
                    // cout << seen[2][i] << ", " << o[i - 1] << endl;
                    // 到 1 或者 3 看谁更优
                    if (seen[2][i - 1] == 0 || seen[2][i - 1] == 1 && o[i - 1] != 3) {
                        cur = 3;
                    } else {
                        cur = 1;
                    }
                    ans += 1;
                } else {
                    if (seen[cur][i - 1] == 0 || seen[cur][i - 1] == 2 && o[i - 1] != 4 - cur) {
                        cur = 4 - cur;
                    } else {
                        cur = 2;
                    }
                    ans += 1;
                }
            }
            // cout << i << " " << cur << endl;
        }
        return ans;
    }
};
/*
[0,3,3,0,3,2,2,0,0,3,0]
[0,2,2,1,0,3,0,3,0,1,0]
[0,0,0,2,0,0,3,3,0,3,0]
*/
