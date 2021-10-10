const int N = 1e5 + 10;
#include <bits/stdc++.h>
using namespace std;

class StockPrice {
   public:
    struct SegmentTree {
        int l, r;
        int datMax, datMin;
    } tree[N * 4];
    int a[N] = {0};
    int cnt = 0, last = -1, lastTime = -1;
    unordered_map<int, int> m;

    // 线段树的建树，时间复杂度：O(N)
    // p 表示节点编号，[l, r] 表示节点所代表的区间
    void build(int p, int l, int r) {
        tree[p].l = l, tree[p].r = r;
        // 叶节点，表示单个元素
        if (l == r) {
            tree[p].datMax = a[l];
            tree[p].datMin = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        // 左子节点：编号为 2*p，代表区间 [l, mid]
        build(2 * p, l, mid);
        // 右子节点：编号为 2*p+1，代表区间 [mid+1, r]
        build(2 * p + 1, mid + 1, r);
        // 从下往上合并更新信息
        tree[p].datMax = max(tree[2 * p].datMax, tree[2 * p + 1].datMax);
        tree[p].datMin = min(tree[2 * p].datMin, tree[2 * p + 1].datMin);
    }

    // 线段树的单点修改，时间复杂度：O(log N)
    // 将 a[x] 的值修改为 v
    void change(int p, int x, int v) {
        // 找到叶节点
        if (tree[p].l == tree[p].r) {
            tree[p].datMax = v;
            tree[p].datMin = v;
            return;
        }
        int mid = (tree[p].l + tree[p].r) >> 1;
        // x 属于左半区间
        if (x <= mid) change(2 * p, x, v);
        // x 属于右半区间
        else
            change(2 * p + 1, x, v);
        // 从下往上合并更新信息
        tree[p].datMax = max(tree[2 * p].datMax, tree[2 * p + 1].datMax);
        tree[p].datMin = min(tree[2 * p].datMin, tree[2 * p + 1].datMin);
    }

    // 线段树的区间查询，时间复杂度：O(log N)
    // 查询序列 a 在区间 [l, r] 上的最大值
    int ask(int p, int l, int r) {
        // 查询区间 [l, r] 完全包含节点 p 所代表的的区间
        if (l <= tree[p].l && r >= tree[p].r) return tree[p].datMax;
        int mid = (tree[p].l + tree[p].r) >> 1;
        // 负无穷大
        int val = -(1 << 30);
        // 左子节点 [tree[p].l, mid] 与查询 [l, r] 有重合
        if (l <= mid) val = max(val, ask(2 * p, l, r));
        // 右子节点 [mid+1, tree[p].r] 与查询 [l, r] 有重合
        if (r >= mid + 1) val = max(val, ask(2 * p + 1, l, r));
        return val;
    }
    int askMin(int p, int l, int r) {
        // 查询区间 [l, r] 完全包含节点 p 所代表的的区间
        if (l <= tree[p].l && r >= tree[p].r) return tree[p].datMin;
        int mid = (tree[p].l + tree[p].r) >> 1;
        // 负无穷大
        int val = (1 << 30);
        // 左子节点 [tree[p].l, mid] 与查询 [l, r] 有重合
        if (l <= mid) val = min(val, askMin(2 * p, l, r));
        // 右子节点 [mid+1, tree[p].r] 与查询 [l, r] 有重合
        if (r >= mid + 1) val = min(val, askMin(2 * p + 1, l, r));
        return val;
    }

    // 调用入口
    // build(1, 1, n);
    // change(1, x, v);
    StockPrice() {
        build(1, 1, 1e5);
    }

    void update(int timestamp, int price) {
        if (lastTime == -1 || timestamp >= lastTime) {
            last = price;
            lastTime = timestamp;
        }
        if (!m[timestamp]) m[timestamp] = ++cnt;
        change(1, m[timestamp], price);
    }

    int current() {
        return last;
    }

    int maximum() {
        return ask(1, 1, cnt);
    }

    int minimum() {
        return askMin(1, 1, cnt);
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */
// [null,null,2308,2308,2308,2308,2308,2308,2308,2308,2308,null,7876,2308,null,7876,1866,1866,7876,null,121,7876,null,7876,7876,5339,null,5339,121,null,null,1866,1866,null,3192,null,9369,null,1006]
// [null,null,2308,2308,2308,2308,2308,2308,2308,2308,2308,null,7876,2308,null,7876,1866,1866,7876,null,121,7876,null,7876,7876,1866,null,1866,121,null,null,1866,1866,null,1866,null,9369,null,1006]
