/*
需要支持「区间增加」和「单点查询」
但是常规的树状数组只支持「单点增加」和「区间查询」
利用差分数组来解决：
x1, x2, ..., xi, ..., xj, ..., xn
原来的差分数组通项 d[i + 1]：
(x{i + 1}) - xi
x1, x2, ..., xi + d, ..., xj + d, ..., xn
现在差分数组，只有 d[i] 和 d[j+1] 需要改变：
xi + d - x{i-1}，x{j + 1} - xj - d

差分数组求前缀和即可得到原数组，y 总经常说的，差分和前缀和互为逆运算

我们可以只求数组的变化值，差分数组维护的是变化情况的差分
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;

int n, m, a[N], x, y, z, c[N];
string s;
int ask(int x) {
    int ans = 0;
    for (; x; x -= x & -x) ans += c[x];
    return ans;
}
void add(int x, int y) {
    for (; x <= n; x += x & -x) c[x] += y;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    while (m--) {
        cin >> s;
        if (s[0] == 'Q') {
            cin >> x;
            int t = ask(x);
            cout << a[x] + t << endl;
        } else {
            cin >> x >> y >> z;
            add(x, z), add(y + 1, -z);
        }
    }
    return 0;
}