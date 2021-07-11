#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;

typedef long long LL;

int t;
LL n, q, p, a[N], pos, val, s, l, r, cmd;

LL qpow(LL a, LL b) {
    LL ans = 1ll;
    while (b) {
        if (b & 1) ans = 1ll * ans * a;
        a = 1ll * a * a;
        b >>= 1;
    }
    return ans;
}

LL V(LL x) {
    if (x == 0 || x % p == x) return 0;
    LL l = 0, r = ceil(log(x) / log(p));
    while (l < r) {
        LL mid = (l + r + 1) >> 1;
        if (x % qpow(p, mid) == 0)
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}

struct SegmentTree {
    int l, r;
    int dat;
} tree[N * 4];

// 线段树的建树，时间复杂度：O(N)
// p 表示节点编号，[l, r] 表示节点所代表的区间
void build(int p, int l, int r) {
    tree[p].l = l, tree[p].r = r;
    // 叶节点，表示单个元素
    if (l == r) {
        tree[p].dat = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    // 左子节点：编号为 2*p，代表区间 [l, mid]
    build(2 * p, l, mid);
    // 右子节点：编号为 2*p+1，代表区间 [mid+1, r]
    build(2 * p + 1, mid + 1, r);
    // 从下往上合并更新信息
    tree[p].dat = max(tree[2 * p].dat, tree[2 * p + 1].dat);
}

// 线段树的单点修改，时间复杂度：O(log N)
// 将 a[x] 的值修改为 v
void change(int p, int x, int v) {
    // 找到叶节点
    if (tree[p].l == tree[p].r) {
        tree[p].dat = v;
        return;
    }
    int mid = (tree[p].l + tree[p].r) >> 1;
    // x 属于左半区间
    if (x <= mid) change(2 * p, x, v);
    // x 属于右半区间
    else
        change(2 * p + 1, x, v);
    // 从下往上合并更新信息
    tree[p].dat = max(tree[2 * p].dat, tree[2 * p + 1].dat);
}

// 线段树的区间查询，时间复杂度：O(log N)
// 查询序列 a 在区间 [l, r] 上的最大值
int ask(int p, int l, int r) {
    // 查询区间 [l, r] 完全包含节点 p 所代表的的区间
    if (l <= tree[p].l && r >= tree[p].r) return tree[p].dat;
    int mid = (tree[p].l + tree[p].r) >> 1;
    // 负无穷大
    int val = -(1 << 30);
    // 左子节点 [tree[p].l, mid] 与查询 [l, r] 有重合
    if (l <= mid) val = max(val, ask(2 * p, l, r));
    // 右子节点 [mid+1, tree[p].r] 与查询 [l, r] 有重合
    if (r >= mid + 1) val = max(val, ask(2 * p + 1, l, r));
    return val;
}

void solve() {
    cin >> n >> q >> p;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);
    while (q--) {
        cin >> cmd;
        if (cmd == 1) {
            cin >> pos >> val;
            change(1, pos, val);
        } else {
            cin >> s >> l >> r;
            LL ans = 0;
            cout << ask(1, l, r) << " ";
        }
    }
    cout << endl;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
