/*
线段树优化的扫描线，时间复杂度为 O(N log N)
*/
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1e4 + 10;

struct Segment {
    int x, y1, y2;
    int k;
    bool operator<(const Segment& b) {
        return x < b.x;
    }
} seg[N * 2];

struct SegmentTree {
    int l, r;
    // 该节点自身被覆盖的次数
    int cnt;
    // 该节点代表的区间被矩形覆盖的长度
    int len;
#define l(x) tree[x].l
#define r(x) tree[x].r
#define cnt(x) tree[x].cnt
#define len(x) tree[x].len
} tree[N * 4];

void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
}

void pushup(int p) {
    if (cnt(p) > 0)
        len(p) = r(p) - l(p) + 1;
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

int n, x1, x2, y1, y2;
int main() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        // 左边为入边，k = 1
        seg[2 * i - 1].x = x1, seg[2 * i - 1].y1 = y1, seg[2 * i - 1].y2 = y2, seg[2 * i - 1].k = 1;
        // 右边为出边，k = -1
        seg[2 * i].x = x2, seg[2 * i].y1 = y1, seg[2 * i].y2 = y2, seg[2 * i].k = -1;
    }
    // 出入边均按照 x 坐标从小到大排序
    sort(seg + 1, seg + 1 + 2 * n);
    int ans = 0;
    build(1, 0, N);
    for (int i = 1; i <= 2 * n; i++) {
        // 计算扫描线在竖直方向上的长度
        int len = len(1);
        ans += len * (seg[i].x - seg[i - 1].x);

        // 注意这里是 seg[i].y2 - 1，因为竖直方向总长度是 y2 - y1
        change(1, seg[i].y1, seg[i].y2 - 1, seg[i].k);
    }
    cout << ans << endl;
    return 0;
}
