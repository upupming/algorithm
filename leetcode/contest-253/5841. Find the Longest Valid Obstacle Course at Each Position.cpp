#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
typedef long long LL;
LL n, a[N], b[N], len[N];
LL c[N];
// 查询前缀和：查询序列 a 第 1~x 个数的和
LL ask(LL x) {
    LL ans = 0;
    for (; x; x -= x & -x) ans = max(ans, c[x]);
    return ans;
}
// 单点增加：给序列中的一个数 a[x] 加上 y
// 算法：自下而上每个节点都要增加 y
void add(int x, LL y) {
    for (; x <= n; x += x & -x) c[x] = max(c[x], y);
}

class Solution {
   public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& a) {
        unordered_map<int, LL> mp;
        memset(c, 0, sizeof c);
        n = a.size();
        a.insert(a.begin(), 0);
        vector<int> ans(n + 1);
        // 离散化
        for (int i = 1; i <= n; i++) {
            b[i] = a[i];
        }
        sort(b + 1, b + n + 1);
        LL m = 0;
        for (int i = 1; i <= n; i++) {
            if (!mp.count(b[i])) {
                mp[b[i]] = ++m;
            }
        }
        for (int i = 1; i <= n; i++) {
            // cout << i << " " << a[i] << " " << mp[a[i]] << " " << ask(mp[a[i]]) << " " << len[i] << endl;
            // cout << "ask " << ask(1) << endl;
            // cout << a[i] << " " << mp[a[i]] << endl;
            ans[i] = max(1ll, ask(mp[a[i]]) + 1);
            // cout << "add " << mp[a[i]] << " " << len[i] << endl;
            add(mp[a[i]], ans[i]);
        }
        ans.erase(ans.begin());
        return ans;
    }
};
