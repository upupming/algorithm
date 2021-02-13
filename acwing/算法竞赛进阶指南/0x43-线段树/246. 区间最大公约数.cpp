/*
要支持区间操作，就必须结合差分来做
性质：
gcd(x, y, z) = gcd(x, y - x, z - y)
线段树维护新数列 B（查分数列 B[i] = A[i] - A[i-1]）的区间和
对于查询 Q l r：
gcd(A[l], ask(1, l+1, r))

A[l] 的维护可以使用树状数组

可以发现，线段树和树状数组都用来实现「单点修改」、「区间查询」，线段树可以维护的信息更加复杂，树状数组一般只用来求一下区间和、最大值
*/
#include <iostream>
using namespace std;
const int N = 5e5 + 10;
typedef long long LL;

int n, m, l, r;
string s;
LL a[N], b[N], c[N], d;
LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}
struct SegmentTree {
    int l, r;
    LL dat;
} t[N * 4];

// 线段树的建树，时间复杂度：O(N)
// p 表示节点编号，[l, r] 表示节点所代表的区间
void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    // 叶节点，表示单个元素
    if (l == r) {
        t[p].dat = b[l];
        return;
    }
    int mid = l + r >> 1;
    // 左子节点：编号为 2*p，代表区间 [l, mid]
    build(2 * p, l, mid);
    // 右子节点：编号为 2*p+1，代表区间 [mid+1, r]
    build(2 * p + 1, mid + 1, r);
    // 从下往上合并更新信息
    t[p].dat = gcd(t[2 * p].dat, t[2 * p + 1].dat);
}

// 线段树的单点修改，时间复杂度：O(log N)
// 将 b[x] 的值修改为 v
void change(int p, int x, LL v) {
    // 找到叶节点
    if (t[p].l == t[p].r) {
        t[p].dat = b[x] = v;
        return;
    }
    int mid = (t[p].l + t[p].r) >> 1;
    // x 属于左半区间
    if (x <= mid) change(2 * p, x, v);
    // x 属于右半区间
    else
        change(2 * p + 1, x, v);
    // 从下往上合并更新信息
    t[p].dat = gcd(t[2 * p].dat, t[2 * p + 1].dat);
}

// 线段树的区间查询，时间复杂度：O(log N)
// 查询序列 a 在区间 [l, r] 上的最大值
LL ask_seg(int p, int l, int r) {
    // 查询区间 [l, r] 完全包含节点 p 所代表的的区间
    if (l <= t[p].l && r >= t[p].r) {
        // cout << t[p].l << " " << t[p].r << " " << t[p].dat << endl;
        return t[p].dat;
    }
    int mid = (t[p].l + t[p].r) >> 1;
    LL gcd_left = 0, gcd_right = 0;
    // 左子节点 [t[p].l, mid] 与查询 [l, r] 有重合
    if (l <= mid) gcd_left = ask_seg(2 * p, l, r);
    // 右子节点 [mid+1, t[p].r] 与查询 [l, r] 有重合
    if (r >= mid + 1) gcd_right = ask_seg(2 * p + 1, l, r);
    // cout << t[p].l << " " << t[p].r << " " << gcd_left << " " << gcd_right << endl;
    // 任何数和 0 取 gcd 保持不变
    return abs(gcd(gcd_left, gcd_right));
}

// 查询前缀和：查询序列 a 第 1~x 个数的和
LL ask(LL x) {
    LL ans = 0;
    for (; x; x -= x & -x) ans += c[x];
    return ans;
}
// 单点增加：给序列中的一个数 a[x] 加上 y
// 算法：自下而上每个节点都要增加 y
void add(int x, LL y) {
    for (; x <= n; x += x & -x) c[x] += y;
}

int main() {
    cin.sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i] - a[i - 1];
    }

    // 调用入口
    build(1, 1, n);
    while (m--) {
        cin >> s;
        if (s[0] == 'Q') {
            cin >> l >> r;
            // cout << a[l] + ask(l) << " " << ask_seg(1, l + 1, r) << endl;
            cout << gcd(a[l] + ask(l), ask_seg(1, l + 1, r)) << endl;
        } else {
            cin >> l >> r >> d;
            // 树状数组记录的只是变化量，使用的时候记得加上 a[i]
            add(l, d), add(r + 1, -d);
            change(1, l, b[l] + d);
            if (r + 1 <= n)
                change(1, r + 1, b[r + 1] - d);
        }
    }
    return 0;
}