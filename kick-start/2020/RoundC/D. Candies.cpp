/*
线段树稍微加了一点变化，将原来的直接加和变成了给出一个公式的加和

只需要「单点修改」，所以无需进行延迟标记

假设维护：a[1] * 1 - a[2] * 2 + a[3] * 3 + ... +
只能求：a[l] * l - a[l+1] * (l+1) + a[l+2] * (l+2)
目标是：a[l] * 1 - a[l+1] *  2    + a[l+2] * 3
需要加上：-a[l] * (l - 1) + a[l+1] * (l - 1) - a[l+2]*(l-1)
        = (-a[l] + a[l+1] - a[l+2] ...) * (l-1)
因此，可以同时维护一个 a[1] - a[2] + a[3] + ... 即可，两个式子做一下数学运算即可得到答案:

dat1 = a[l] * l - a[l+1] * (l+1) + a[l+2] * (l+2) + ...
dat2 = (a[l] - a[l+1] + a[l+2] + ...)
ans = dat1 - dat2 * (l-1)

上面分析的是 l 是奇数的情况，对于 l 是偶数的情况：
-a[l] * l + a[l+1] * (l+1) - a[l+2] * (l+2)
+
(a[l] - a[l+1] + a[l+2] ...) * (l-1)
结果即是：
- a[l] * 1 + a[l+1] * 2 - a[l+2] * 3
所以，最后在结果上加一个负号即可

dat1 = -(a[l] * l - a[l+1] * (l+1) + a[l+2] * (l+2) + ...)
dat2 = -(a[l] - a[l+1] + a[l+2] + ...)
ans = -(dat1 - dat2 * (l-1))

也就只需要维护：

dat1 = a[1] * 1 - a[2] * 2 + a[3] * 3 + ... +
dat2 = a[1] - a[2] + a[3] + ... +
*/
#include <iostream>
using namespace std;
const int N = 2e5 + 10;
typedef long long LL;

int tt, a[N], n, q, x, y;
string op;
struct SegmentTree {
    int l, r;
    LL dat1 = 0, dat2 = 0, ans;
} t[N * 4];

// 返回 (-1)^x
int sign(int x) {
    if (x % 2) return -1;
    return 1;
}
// 线段树的建树，时间复杂度：O(N)
// p 表示节点编号，[l, r] 表示节点所代表的区间
void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    // 叶节点，表示单个元素
    if (l == r) {
        // 修改此处单个节点的定义
        t[p].dat1 = -sign(l) * l * a[l];
        t[p].dat2 = -sign(l) * a[l];
        return;
    }
    int mid = (l + r) >> 1;
    // 左子节点：编号为 2*p，代表区间 [l, mid]
    build(2 * p, l, mid);
    // 右子节点：编号为 2*p+1，代表区间 [mid+1, r]
    build(2 * p + 1, mid + 1, r);
    // 从下往上合并更新信息
    t[p].dat1 = t[2 * p].dat1 + t[2 * p + 1].dat1;
    t[p].dat2 = t[2 * p].dat2 + t[2 * p + 1].dat2;
}

// 线段树的单点修改，时间复杂度：O(log N)
// 将 a[x] 的值修改为 v
void change(int p, int x, int v) {
    // 找到叶节点
    if (t[p].l == t[p].r) {
        t[p].dat1 = -sign(t[p].l) * t[p].l * v;
        t[p].dat2 = -sign(t[p].l) * v;
        return;
    }
    int mid = (t[p].l + t[p].r) >> 1;
    // x 属于左半区间
    if (x <= mid) change(2 * p, x, v);
    // x 属于右半区间
    else
        change(2 * p + 1, x, v);
    // 从下往上合并更新信息
    t[p].dat1 = t[2 * p].dat1 + t[2 * p + 1].dat1;
    t[p].dat2 = t[2 * p].dat2 + t[2 * p + 1].dat2;
}

// 线段树的区间查询，时间复杂度：O(log N)
// 查询序列 a 在区间 [l, r] 上的最大值
SegmentTree ask(int p, int l, int r) {
    // 查询区间 [l, r] 完全包含节点 p 所代表的的区间
    if (l <= t[p].l && r >= t[p].r) {
        // 一定要注意，这里也要计算一下 ans，否则如果直接查询整个 1-n 区间，返回的答案就有问题了
        auto &c = t[p];
        c.ans = (c.dat1 - c.dat2 * (l - 1)) * sign(l + 1);
        return t[p];
    }
    int mid = (t[p].l + t[p].r) >> 1;

    SegmentTree a, b, c;
    if (l <= mid) {
        a = ask(2 * p, l, r);
        c.dat1 += a.dat1;
        c.dat2 += a.dat2;
    }
    if (r >= mid + 1) {
        b = ask(2 * p + 1, l, r);
        c.dat1 += b.dat1;
        c.dat2 += b.dat2;
    }

    // 注意：dat1 里面计算的时候就已经乘过 l 了，这里不要再乘一次，否则不对
    c.ans = (c.dat1 - c.dat2 * (l - 1)) * sign(l + 1);
    // cout << t[p].l << " " << t[p].r << " " << c.dat1 << " " << c.dat2 << " " << c.ans << endl;
    return c;
}
LL solve() {
    LL ans = 0;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // 调用入口
    build(1, 1, n);

    while (q--) {
        cin >> op >> x >> y;
        if (op[0] == 'Q') {
            LL r = ask(1, x, y).ans;
            // cout << x << " " << y << " " << r << endl;
            ans += r;
        } else {
            change(1, x, y);
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