/*
支持「单点修改」和「区间查询」，可以使用线段树
区间查询的计算方式比较复杂：
要求的是 t[p].dat: 区间最大连续子段和
怎么由两个子节点 2*p 和 2*p+1 求得？
应该是这几个情况中的最大值：
1. 2*p 的最大连续子段和
2. 2*p + 1 的最大连续子段和
3. (2*p 的紧靠右端的最大连续子段和) + (2*p+1 的紧靠左端的最大连续子段和)
因此，我们需要定义：
t[p].lmax: 节点 p 代表的区间上紧靠左端的最大连续子段和
t[p].rmax: 节点 p 代表的区间上紧靠右端的最大连续子段和
*/
#include <climits>
#include <iostream>
using namespace std;
const int N = 5e5 + 10;

int a[N], n, m, op, x, y;
struct SegmentTree {
    int l, r;
    int dat, lmax, rmax, sum;
} t[N * 4];

// 线段树的建树，时间复杂度：O(N)
// p 表示节点编号，[l, r] 表示节点所代表的区间
void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    // 叶节点，表示单个元素
    if (l == r) {
        t[p].dat = t[p].lmax = t[p].rmax = t[p].sum = a[l];
        return;
    }
    int mid = l + r >> 1;
    // 左子节点：编号为 2*p，代表区间 [l, mid]
    build(2 * p, l, mid);
    // 右子节点：编号为 2*p+1，代表区间 [mid+1, r]
    build(2 * p + 1, mid + 1, r);
    // 从下往上合并更新信息
    t[p].sum = t[2 * p].sum + t[2 * p + 1].sum;
    t[p].lmax = max(
        t[2 * p].lmax,
        t[2 * p].sum + t[2 * p + 1].lmax);
    t[p].rmax = max(
        t[2 * p + 1].rmax,
        t[2 * p + 1].sum + t[2 * p].rmax);
    t[p].dat = max(max(
                       t[2 * p].dat,
                       t[2 * p + 1].dat),
                   t[2 * p].rmax + t[2 * p + 1].lmax);
}

// 线段树的单点修改，时间复杂度：O(log N)
// 将 a[x] 的值修改为 v
void change(int p, int x, int v) {
    // 找到叶节点
    if (t[p].l == t[p].r) {
        t[p].dat = t[p].lmax = t[p].rmax = t[p].sum = v;
        return;
    }
    int mid = (t[p].l + t[p].r) >> 1;
    // x 属于左半区间
    if (x <= mid) change(2 * p, x, v);
    // x 属于右半区间
    else
        change(2 * p + 1, x, v);
    // 从下往上合并更新信息
    t[p].sum = t[2 * p].sum + t[2 * p + 1].sum;
    t[p].lmax = max(
        t[2 * p].lmax,
        t[2 * p].sum + t[2 * p + 1].lmax);
    t[p].rmax = max(
        t[2 * p + 1].rmax,
        t[2 * p + 1].sum + t[2 * p].rmax);
    t[p].dat = max(max(
                       t[2 * p].dat,
                       t[2 * p + 1].dat),
                   t[2 * p].rmax + t[2 * p + 1].lmax);
}

// 线段树的区间查询，时间复杂度：O(log N)
// 查询序列 a 在区间 [l, r] 上的最大值
SegmentTree ask(int p, int l, int r) {
    // 查询区间 [l, r] 完全包含节点 p 所代表的的区间
    if (l <= t[p].l && r >= t[p].r) return t[p];
    int mid = (t[p].l + t[p].r) >> 1;
    // 这里必须除以 2，不然可能下溢，产生很大的整数，从而的得到一个错误的结果
    int val = INT_MIN / 2;
    SegmentTree a, b, c;
    // 左子节点
    a.dat = a.sum = a.lmax = a.rmax = val;
    // 右子节点
    b.dat = b.sum = b.lmax = b.rmax = val;
    c.sum = 0;
    // 左子节点 [t[p].l, mid] 与查询 [l, r] 有重合
    if (l <= mid) {
        a = ask(2 * p, l, r);
        c.sum += a.sum;
    }
    // 右子节点 [mid+1, t[p].r] 与查询 [l, r] 有重合
    if (r >= mid + 1) {
        b = ask(2 * p + 1, l, r);
        c.sum += b.sum;
    }
    c.lmax = max(a.lmax, b.lmax + a.sum);
    // 没有左子节点的时候，a.sum = -INF
    if (l > mid)
        c.lmax = max(c.lmax, b.lmax);
    c.rmax = max(b.rmax, b.sum + a.rmax);
    // 没有右子节点的时候，b.sum = -INF
    if (r < mid + 1)
        c.rmax = max(c.rmax, a.rmax);
    // cout << a.dat << " " << b.dat << " " << a.rmax << " " << b.lmax << endl;
    c.dat = max(max(a.dat, b.dat), a.rmax + b.lmax);
    // cout << t[p].l << " " << t[p].r << " " << c.dat << endl;
    return c;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    // 调用入口
    build(1, 1, n);
    while (m--) {
        cin >> op >> x >> y;
        if (op == 1) {
            if (x > y) swap(x, y);
            cout << ask(1, x, y).dat << endl;
        } else
            change(1, x, y);
    }

    return 0;
}