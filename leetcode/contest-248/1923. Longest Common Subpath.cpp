#include <bits/stdc++.h>
using namespace std;
const int P = 1333331;
const int N = 1e5 + 10;
// 字符串哈希+二分，参考: https://leetcode-cn.com/problems/longest-duplicate-substring/solution/zui-chang-zhong-fu-zi-chuan-by-leetcode/
typedef unsigned long long ULL;
ULL f[N], g[N];
vector<int> common, last;
ULL myPow(ULL a, ULL b) {
    ULL ans = 1;
    while (b) {
        if (b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}
ULL getHash(ULL f[], int l, int r) {
    return f[r] - f[l - 1] * myPow(P, r - l + 1);
}
void out(vector<int> a) {
    cout << "size: " << a.size() << endl;
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}
class Solution {
   public:
    int longestCommonSubpath(int n, vector<vector<int>>& paths) {
        int m = paths.size();
        if (m == 1) return paths[0].size();
        int len0 = paths[m - 2].size(), len1 = paths[m - 1].size();

        for (int i = 1; i <= len0; i++) {
            f[i] = f[i - 1] * P + paths[m - 2][i - 1];
        }
        for (int i = 1; i <= len1; i++) {
            g[i] = g[i - 1] * P + paths[m - 1][i - 1];
        }

        const auto valid = [len0, len1, m, &paths](int mid) {
            common.clear();
            if (mid == 0) return true;
            unordered_set<ULL> s;
            for (int i = 1; i + mid - 1 <= len0; i++) {
                int j = i + mid - 1;
                // cout << i << " " << j << " " << getHash(f, i, j) << endl;
                s.insert(getHash(f, i, j));
            }
            for (int i = 1; i + mid - 1 <= len1; i++) {
                int j = i + mid - 1;
                // cout << i << "m " << j << " " << getHash(g, i, j) << endl;
                if (s.count(getHash(g, i, j))) {
                    // cout << "count" << endl;
                    for (int k = i; k <= j; k++) {
                        common.push_back(paths[m - 1][k - 1]);
                    }
                    return true;
                }
            }
            return false;
        };

        int len = min(len0, len1);
        int l = 0, r = len;
        last.clear();
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (valid(mid)) {
                l = mid;
                last = common;
            } else
                r = mid - 1;
        }
        // cout << l << endl;
        if (l == 0) return 0;
        // out(last);
        paths.pop_back(), paths.pop_back();
        paths.push_back(last);
        return longestCommonSubpath(n, paths);
    }
};
