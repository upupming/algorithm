/*
a[x] 增加的值：
b[1] + b[2] + ... b[x]
a[1~x] 增加的值：
b[1] +
b[1] + b[2] +
... +
b[1] + b[2] + ... b[x]
等价于：
x b[1] + (x-1) b[2] + ... + 1 b[x]
等价于：
(x+1)(b[1] + ... + b[x]) -
(b[1] + 2b[2] + ... + xb[x])

用两个树状数组，维护 b[i] 前缀和，以及 ib[i] 的前缀和，通过上面的公式即可计算出结果
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
typedef long long LL;

// c[0] 是 b[i] 的树状数组，c[1] 是 ib[i] 的树状数组
LL n, m, x, y, z, a[N], c[2][N], sum[N];
string s;
LL ask(int k, int x) {
    LL ans = 0;
    for (; x; x -= x & -x) ans += c[k][x];
    return ans;
}
void add(int k, int x, int y) {
    for (; x <= n; x += x & -x) c[k][x] += y;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    while (m--) {
        cin >> s;
        if (s[0] == 'Q') {
            cin >> x >> y;
            // t[y] - t[x-1]
            x--;
            auto tx0 = ask(0, x), tx1 = ask(1, x);
            // cout << tx0 << " " << tx1 << endl;
            // 计算公式
            auto ans0 = (x + 1) * tx0 - tx1;
            auto ty0 = ask(0, y), ty1 = ask(1, y);
            // cout << ty0 << " " << ty1 << endl;
            auto ans1 = (y + 1) * ty0 - ty1;
            // cout << ans1 << " " << ans0 << " " << sum[y] << " " << sum[x] << endl;
            cout << ans1 - ans0 + (sum[y] - sum[x]) << endl;
        } else {
            cin >> x >> y >> z;
            add(0, x, z), add(0, y + 1, -z);
            add(1, x, x * z), add(1, y + 1, -(y + 1) * z);
        }
    }
    return 0;
}

/*
下标： 1 2 3 4 5 6 7
模拟： C 3 6 3
// b[i]
起始： 0 0 0 0 0 0
之后： 0 0 3 3 3 3
前缀和：0 0 3 0 0 0 -3
// ib[i]
只有 b[x] 和 b[y+1] 发生了变化，变化值分别为 z 和 -z，
因此分别乘上对应的下标即可：x * z，(y + 1) * (-z)
*/