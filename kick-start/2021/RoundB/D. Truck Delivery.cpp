#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10, Q = 1e5 + 10, LMax = 2e5 + 10;
typedef long long LL;

int t, n, q;
vector<int> e[N];
// 节点 x: pair<w, index>
vector<pair<int, int>> query[N];
unordered_map<int, unordered_map<int, int>> L;
unordered_map<int, unordered_map<int, LL>> A;
LL ans[Q];

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

struct SegmentTree {
    int l, r;
    LL dat;
} tree[LMax * 4];

// 线段树的建树，时间复杂度：O(N)
// p 表示节点编号，[l, r] 表示节点所代表的区间
void build(int p, int l, int r) {
    tree[p].l = l, tree[p].r = r;
    // 叶节点，表示单个元素
    if (l == r) {
        tree[p].dat = 0;
        return;
    }
    int mid = (l + r) >> 1;
    // 左子节点：编号为 2*p，代表区间 [l, mid]
    build(2 * p, l, mid);
    // 右子节点：编号为 2*p+1，代表区间 [mid+1, r]
    build(2 * p + 1, mid + 1, r);
    // 从下往上合并更新信息
    tree[p].dat = gcd(tree[2 * p].dat, tree[2 * p + 1].dat);
}

// 线段树的单点修改，时间复杂度：O(log N)
// 将 a[x] 的值修改为 v
void change(int p, int x, LL v) {
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
    tree[p].dat = gcd(tree[2 * p].dat, tree[2 * p + 1].dat);
}

// 线段树的区间查询，时间复杂度：O(log N)
// 查询序列 a 在区间 [l, r] 上的 gcd
LL ask(int p, int l, int r) {
    // 查询区间 [l, r] 完全包含节点 p 所代表的的区间
    if (l <= tree[p].l && r >= tree[p].r) return tree[p].dat;
    int mid = (tree[p].l + tree[p].r) >> 1;

    LL val = 0;
    // 左子节点 [tree[p].l, mid] 与查询 [l, r] 有重合
    if (l <= mid) val = gcd(val, ask(2 * p, l, r));
    // 右子节点 [mid+1, tree[p].r] 与查询 [l, r] 有重合
    if (r >= mid + 1) val = gcd(val, ask(2 * p + 1, l, r));
    return val;
}

void dfs(int x, int fa) {
    // assert 之前没有插入过 l，对应题目没有重复 l 的条件「All L_i are distinct.」
    assert(ask(1, L[x][fa], L[x][fa]) == 0);
    change(1, L[x][fa], A[x][fa]);
    // 回答所有对 x 的查询
    for (auto &[w, idx] : query[x]) {
        ans[idx] = ask(1, 0, w);
    }
    for (auto &y : e[x]) {
        if (y != fa) {
            dfs(y, x);
        }
    }
    change(1, L[x][fa], 0);
}

void solve() {
    memset(tree, 0, sizeof tree);
    memset(ans, 0, sizeof ans);
    build(1, 0, LMax);
    // query 的下标是节点标号，所以循环是从 1 到 n 不是 1 到 q，小细节出错 debug 了几个小时，哭了
    for (int i = 1; i <= n; i++) query[i].clear();
    for (int i = 1; i <= q; i++) {
        int c, w;
        cin >> c >> w;
        query[c].push_back(make_pair(w, i));
    }
    dfs(1, -1);
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> q;
        for (int i = 1; i <= n; i++) e[i].clear();
        L.clear(), A.clear();
        for (int i = 0; i < n - 1; i++) {
            int x, y, l;
            LL a;
            cin >> x >> y >> l >> a;
            e[x].push_back(y);
            e[y].push_back(x);
            L[x][y] = L[y][x] = l;
            A[x][y] = A[y][x] = a;
        }
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
