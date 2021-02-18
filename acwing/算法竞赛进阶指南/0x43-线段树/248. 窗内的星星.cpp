/*
问题可以转化为：平面上有若干个区域，每个区域都带有一个权值，求在哪个坐标上重叠的区域权值和最大

线段树维护 y 轴方向上区间最大值 dat，扫描线自左向右移动，用根节点的 dat 值更新答案
*/
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1e4 + 10;

struct Segment {
    long long x, y1, y2;
    // 亮度
    int c;
    bool operator<(const Segment& b) {
        return x < b.x || (x == b.x && c < b.c);
    }
} seg[N * 2];

// raw[i] 表示整数值 i 对应的原始 y 坐标
int raw[N << 1];

struct SegmentTree {
    int l, r;
    // 区间最大亮度和
    int dat, lazy;
#define l(x) tree[x].l
#define r(x) tree[x].r
#define dat(x) tree[x].dat
#define lazy(x) tree[x].lazy
} tree[N * 8];

void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
}

void pushup(int p) {
    dat(p) = max(dat(2 * p), dat(2 * p + 1));
}

void spread(int p) {
    // 节点 p 有延迟标记的话
    if (lazy(p)) {
        // 更新左子节点信息，延迟值 * 区间长度等于节点的增加量
        dat(2 * p) += lazy(p);
        // 更新右子节点信息
        dat(2 * p + 1) += lazy(p);
        // 给左子节点打延迟标记
        lazy(2 * p) += lazy(p);
        // 给右子节点打延迟标记
        lazy(2 * p + 1) += lazy(p);
        // 清除 p 的标记
        lazy(p) = 0;
    }
}

void change(int p, int l, int r, int c) {
    // 完全覆盖
    if (l <= l(p) && r >= r(p)) {
        dat(p) += c;
        lazy(p) += c;
        return;
    }
    spread(p);
    int mid = (l(p) + r(p)) >> 1;
    // 和左子节点有相交部分
    if (l <= mid) change(2 * p, l, r, c);
    // 和右子节点有相交部分
    if (r >= mid + 1) change(2 * p + 1, l, r, c);
    pushup(p);
}

int n, w, h;
long long x, y, c;
int main() {
    while (cin >> n >> w >> h) {
        for (int i = 1; i <= n; i++) {
            cin >> x >> y >> c;
            // 本来应该是以 (x, y) 为中心的矩形，但是将整个坐标系平移到以 (x, y) 为左下角的矩形，是不影响的
            // 左边为入边，k = c
            seg[2 * i - 1].x = x, seg[2 * i - 1].y1 = y, seg[2 * i - 1].y2 = y + h, seg[2 * i - 1].c = c;
            // 右边为出边，k = -c
            seg[2 * i].x = x + w, seg[2 * i].y1 = y, seg[2 * i].y2 = y + h, seg[2 * i].c = -c;

            // 离散化
            raw[2 * i - 1] = y, raw[2 * i] = y + h;
        }
        // 离散化
        sort(raw + 1, raw + 1 + 2 * n);
        int m = unique(raw + 1, raw + 1 + 2 * n) - (raw + 1);
        // 直接替换成离散化后的值，方便线段树操作，省去 map
        for (int i = 1; i <= 2 * n; i++) {
            seg[i].y1 = lower_bound(raw + 1, raw + m + 1, seg[i].y1) - raw;
            seg[i].y2 = lower_bound(raw + 1, raw + m + 1, seg[i].y2) - raw;
        }
        // 出入边均按照 x 坐标从小到大排序
        sort(seg + 1, seg + 1 + 2 * n);
        build(1, 1, m);
        int ans = 0;
        for (int i = 1; i <= 2 * n; i++) {
            change(1, seg[i].y1, seg[i].y2 - 1, seg[i].c);
            ans = max(ans, dat(1));
        }
        cout << ans << endl;
    }
    return 0;
}
