#include <bits/stdc++.h>
using namespace std;

int t, r, c, k, r1, r2, c1, c2;
typedef long long LL;

void add(LL& ans, int d) {
    ans += (d + k - 1) / k;
}
LL calc() {
    LL ans = 0;

    if (r1 > 1) add(ans, c2);
    if (c2 < c) add(ans, r2 - r1 + 1);
    if (r2 < r) add(ans, c2 - c1 + 1);
    if (c1 > 1) add(ans, r2 - r1 + 1);
    int rCnt = r2 - r1 - 1;
    LL s = (c2 - c1 + 1 + k - 1) / k;
    ans += s * rCnt;
    int cCnt = c2 - c1 - 1;
    s = (r2 - r1 + 1 + k - 1) / k;
    ans += s * cCnt;
    return ans;
}

void solve() {
    cin >> r >> c >> k;
    cin >> r1 >> c1 >> r2 >> c2;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
