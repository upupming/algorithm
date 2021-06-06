/*
读题的时候漏了 sum(boxes[j].length) <= 10^5
以为 1 <= boxes[j].length <= 10^5，一看 m = 10^5 以为没法做了
反倒比 T3 还简单些，因为只需要 lower_bound 一下就好了
*/
#include <bits/stdc++.h>
using namespace std;
const int P = 1e9 + 7;
typedef long long LL;
class Solution {
   public:
    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {
        int n = packages.size();
        vector<LL> sum(n + 1);
        sort(packages.begin(), packages.end());
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + packages[i - 1];
        }
        LL ans = 1e12;
        for (auto& box : boxes) {
            LL tmp = 0;
            sort(box.begin(), box.end());
            LL i = 0, j = 0;
            for (auto& b : box) {
                // 这一步是关键优化
                j = upper_bound(packages.begin(), packages.end(), b) - packages.begin();
                // sum[i~j-1]，注意 sum 下标从 1 开始
                tmp += (j - i) * b - (sum[j] - sum[i]);
                i = j;
                if (i == n) break;
            }
            if (i == n)
                ans = min(ans, tmp);
        }
        return ans == 1e12 ? -1 : ans % P;
    }
};
