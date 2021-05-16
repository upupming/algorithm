#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1010, P = 1e9 + 7;
LL f[N][N];
class Solution {
   public:
    int rearrangeSticks(int n, int k) {
        memset(f, 0, sizeof f);
        f[1][1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int k = 1; k <= n; k++) {
                f[i][k] += (f[i - 1][k - 1] + f[i - 1][k] * (i - 1)) % P;
                // cout << i << " " << k << " " << f[i][k] << endl;
            }
        }
        return f[n][k];
    }
};
