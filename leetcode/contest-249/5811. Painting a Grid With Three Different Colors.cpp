#include <bits/stdc++.h>
using namespace std;
const int P = 1e9 + 7;
typedef long long LL;

/*
就是 https://leetcode-cn.com/problems/number-of-ways-to-paint-n-3-grid/solution/gei-n-x-3-wang-ge-tu-tu-se-de-fang-an-shu-by-leetc/ 的拓展版本
*/

LL qpow(LL a, LL b, LL p = P) {
    LL ans = 1ll % p;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return ans;
}
class Solution {
    int m, n;
    vector<int> types;
    void dfs(int dep, int last, int s) {
        if (dep == m) {
            types.push_back(s);
            return;
        }
        for (int i = 0; i < 3; i++) {
            if (i != last) {
                dfs(dep + 1, i, s + i * qpow(3, dep));
            }
        }
    }

   public:
    int colorTheGrid(int _m, int _n) {
        m = _m, n = _n;
        // 预处理出所有满足条件的 type
        dfs(0, -1, 0);
        int type_cnt = types.size();
        // 预处理出所有可以作为相邻行的 type 对
        vector<vector<int>> related(type_cnt, vector<int>(type_cnt));
        for (int i = 0; i < type_cnt; ++i) {
            // 得到 types[i] 三个位置的颜色
            for (int j = 0; j < type_cnt; ++j) {
                bool ok = true;
                for (int k = 0; k < m; k++) {
                    int y1 = types[j] / qpow(3, k) % 3;
                    int x1 = types[i] / qpow(3, k) % 3;
                    if (x1 == y1) {
                        ok = false;
                        break;
                    }
                }
                // cout << i << " " << j << " " << types[i] << " " << types[j] << endl;
                if (ok) related[i][j] = related[j][i] = 1;
            }
        }
        // 递推数组
        vector<vector<int>> f(n + 1, vector<int>(type_cnt));
        // 边界情况，第一行可以使用任何 type
        for (int i = 0; i < type_cnt; ++i) {
            f[1][i] = 1;
        }
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < type_cnt; ++j) {
                for (int k = 0; k < type_cnt; ++k) {
                    // f[i][j] 等于所有 f[i - 1][k] 的和
                    // 其中 k 和 j 可以作为相邻的行
                    if (related[k][j]) {
                        f[i][j] += f[i - 1][k];
                        f[i][j] %= P;
                    }
                }
            }
        }
        // 最终所有的 f[n][...] 之和即为答案
        int ans = 0;
        for (int i = 0; i < type_cnt; ++i) {
            ans += f[n][i];
            ans %= P;
        }
        return ans;
    }
};
