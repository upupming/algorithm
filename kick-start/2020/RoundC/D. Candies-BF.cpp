/*
线段树解法一直 WA，因此写一个暴力解法用来对拍
最后检查发现是区间完全覆盖时没有对 ans 进行计算
*/
#include <iostream>
using namespace std;
const int N = 2e5 + 10;
typedef long long LL;

int tt, a[N], n, q, x, y;
string op;

LL sign(LL x) {
    if (x % 2) return -1;
    return 1;
}
LL solve() {
    LL ans = 0;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];

    while (q--) {
        cin >> op >> x >> y;
        if (op[0] == 'Q') {
            LL r = 0;
            for (int i = x, j = 1; i <= y; i++, j++) {
                r += a[i] * j * sign(j + 1);
            }
            cout << x << " " << y << " " << r << endl;
            ans += r;
        } else {
            a[x] = y;
        }
    }
    return ans;
}
int main() {
    cin >> tt;
    for (int i = 1; i <= tt; i++) {
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}

/*
2
5 4
1 3 9 8 2
Q 2 4
Q 5 5
U 2 10
Q 1 2
*/