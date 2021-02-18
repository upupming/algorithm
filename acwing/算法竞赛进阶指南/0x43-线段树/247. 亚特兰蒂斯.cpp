/*
需要加一个离散化，其他过程都是一样的
*/
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
const int N = 1e4 + 10;

struct Segment {
    double x, y1, y2;
    int k;
    bool operator<(const Segment& b) {
        return x < b.x;
    }
} seg[N * 2];
// raw[i] 表示整数值 i 对应的原始 y 坐标
double raw[N << 1];
// val[y] 表示 y 坐标对应的整数 hash 值
map<double, int> val;

struct SegmentTree {
    int l, r;
    // 该节点自身被覆盖的次数
    int cnt;
    // 该节点代表的区间被矩形覆盖的长度
    double len;
#define l(x) tree[x].l
#define r(x) tree[x].r
#define cnt(x) tree[x].cnt
#define len(x) tree[x].len
    // 注意这里要开 8 被空间，否则会 Segmentation Fault
    // 离散化的总元素（y坐标数量）个数是 2*N，线段树本身要求 4 倍，因此就是 8 倍了。
} tree[N * 8];

void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
}

void pushup(int p) {
    if (cnt(p) > 0)
        len(p) = raw[r(p) + 1] - raw[l(p)];
    else {
        if (l(p) == r(p))
            len(p) = 0;
        else
            len(p) = len(2 * p) + len(2 * p + 1);
    }
}

void change(int p, int l, int r, int k) {
    // 完全覆盖
    if (l <= l(p) && r >= r(p)) {
        cnt(p) += k;
        pushup(p);
        return;
    }
    int mid = (l(p) + r(p)) >> 1;
    // 和左子节点有相交部分
    if (l <= mid) change(2 * p, l, r, k);
    // 和右子节点有相交部分
    if (r >= mid + 1) change(2 * p + 1, l, r, k);
    pushup(p);
}

int n, t;
double x1, y1, x2, y2;
int main() {
    while (cin >> n && n) {
        for (int i = 1; i <= n; i++) {
            cin >> x1 >> y1 >> x2 >> y2;
            // 左边为入边，k = 1
            seg[2 * i - 1].x = x1, seg[2 * i - 1].y1 = y1, seg[2 * i - 1].y2 = y2, seg[2 * i - 1].k = 1;
            // 右边为出边，k = -1
            seg[2 * i].x = x2, seg[2 * i].y1 = y1, seg[2 * i].y2 = y2, seg[2 * i].k = -1;

            // 离散化
            raw[2 * i - 1] = y1, raw[2 * i] = y2;
        }
        // 离散化
        sort(raw + 1, raw + 1 + 2 * n);
        int m = unique(raw + 1, raw + 1 + 2 * n) - (raw + 1);
        // m 个不同的 y 坐标分别映射到 1-m
        for (int i = 1; i <= m; i++) val[raw[i]] = i;
        // 出入边均按照 x 坐标从小到大排序
        sort(seg + 1, seg + 1 + 2 * n);
        build(1, 1, m);
        double ans = 0;
        for (int i = 1; i <= 2 * n; i++) {
            // 计算扫描线在竖直方向上的长度
            double len = len(1);
            ans += len * (seg[i].x - seg[i - 1].x);

            // 注意这里是 seg[i].y2 - 1
            int y1 = val[seg[i].y1], y2 = val[seg[i].y2] - 1;
            change(1, y1, y2, seg[i].k);
            // cout << i << " " << ans << endl;
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n", ++t, ans);
    }
}
