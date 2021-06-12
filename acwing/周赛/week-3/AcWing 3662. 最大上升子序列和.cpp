#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;
const int N = 1e5 + 10;
typedef long long LL;
typedef pair<LL, LL> PLL;
LL n, a[N], b[N], sum[N], maxSum[N];
unordered_map<int, LL> mp;
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
    for (; x < N; x += x & -x) c[x] = max(c[x], y);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // 离散化
    memcpy(b, a, sizeof a);
    sort(b + 1, b + n + 1);
    LL m = 0;
    for (int i = 1; i <= n; i++) {
        if (!mp.count(b[i]))
            mp[b[i]] = ++m;
    }

    // DP 过程，使用树状数组优化
    for (int i = 1; i <= n; i++) {
        sum[i] = max(mp[a[i]], ask(mp[a[i]] - 1) + a[i]);
        add(mp[a[i]], sum[i]);
        // sum[i] = a[i];
        // for (int j = 1; j < a[i]; j++) {
        //     sum[i] = max(sum[i], maxSum[j] + a[i]);
        // }
        // maxSum[a[i]] = max(maxSum[a[i]], sum[i]);
    }

    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, sum[i]);
    }
    cout << ans << endl;
    return 0;
}
