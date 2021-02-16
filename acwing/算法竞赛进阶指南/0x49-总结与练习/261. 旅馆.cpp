/*
因为需要区间更新，所以需要延迟标记来降低复杂度

维护一个长度为 n 的 01 串，初始全为 0，进行 m 次操作：
1. 找到最靠左的长度为 len 的全部为 0 的子串，输出左端点并把这个子串全部赋值为 1，如果不存在就输出 0
2. 把左端点为 l 长度为 len 的子串全部赋值为 0

需要在节点上维护三个信息：
- d: 区间内最长的 0 串长度
- ld: 区间内以左端点开始的最长 0 串长度
- rd: 区间内以右端点结束的最长 0 串长度
node.d = max(
    left.d,
    right.d,
    left.rd + right.ld
)

因为分配的时候，要找的是最左边的全 0 串，因此先访问左子节点再访问右子节点
*/
#include <iostream>
using namespace std;
const int N = 5e4 + 10;

// 注意：有延迟标记的节点，本身已经完成了数据更新，只是没有传递给子节点
struct SegmentTree {
    int l, r;
    long long d, ld, rd;
    long long lazy;
#define l(x) tree[x].l
#define r(x) tree[x].r
#define d(x) tree[x].d
#define ld(x) tree[x].ld
#define rd(x) tree[x].rd
#define lazy(x) tree[x].lazy
} tree[N * 4];

void pushup(int p) {
    int left = 2 * p, right = 2 * p + 1;
    ld(p) = ld(left);
    // 左边全 0 的话
    if (d(left) == r(left) - l(left) + 1)
        ld(p) = d(left) + ld(right);
    rd(p) = rd(right);
    // 右边全 0 的话
    if (d(right) == r(right) - l(right) + 1)
        rd(p) = d(right) + rd(left);
    d(p) = max(d(left), d(right));
    d(p) = max(d(p), rd(left) + ld(right));
}
void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    if (l == r) {
        // 长度为 1 的空房间（串 0）
        d(p) = ld(p) = rd(p) = 1;
        return;
    }
    int mid = l + r >> 1;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    pushup(p);
}
void spread(int p) {
    // 节点 p 有延迟标记的话
    if (lazy(p)) {
        int left = 2 * p, right = 2 * p + 1;
        // 房间需要清空的话
        if (lazy(p) == 1) {
            d(left) = ld(left) = rd(left) = r(left) - l(left) + 1;
            d(right) = ld(right) = rd(right) = r(right) - l(right) + 1;
        } else if (lazy(p) == 2) {
            d(left) = ld(left) = rd(left) = 0;
            d(right) = ld(right) = rd(right) = 0;
        }

        // 给子节点打延迟标记
        lazy(left) = lazy(right) = lazy(p);
        // 清除 p 的标记
        lazy(p) = 0;
    }
}

void change(int p, int l, int r, int c) {
    // 完全覆盖
    if (l <= l(p) && r >= r(p)) {
        // c == 1 表示清空，全 0 串的长度恢复
        if (c == 1)
            d(p) = ld(p) = rd(p) = r(p) - l(p) + 1;
        // c == 2 表示分配，全 0 串长度变为 0
        else
            d(p) = ld(p) = rd(p) = 0;
        // c 的取值只能是 1、2，0 表示没有懒标记
        lazy(p) = c;
        return;
    }
    // 因为即将访问下面的节点了，必须先下传延迟标记
    spread(p);
    int mid = (l(p) + r(p)) >> 1;
    // 和左子节点有相交部分
    if (l <= mid) change(2 * p, l, r, c);
    // 和右子节点有相交部分
    if (r >= mid + 1) change(2 * p + 1, l, r, c);
    pushup(p);
}

// 分配 len 长度的连续空房间
long long ask(int p, int len) {
    if (d(p) < len) return 0;
    // 因为即将访问下面的节点了，必须先下传延迟标记
    spread(p);
    int mid = l(p) + r(p) >> 1;
    int left = 2 * p, right = 2 * p + 1;
    if (d(left) >= len) return ask(left, len);
    if (rd(left) + ld(right) >= len) return r(left) - rd(left) + 1;
    if (d(right) >= len) return ask(right, len);
    return 0;
}

int n, m, op, x, d;
int main() {
    cin >> n >> m;
    build(1, 1, n);
    while (m--) {
        cin >> op;
        if (op == 1) {
            cin >> d;
            int l = ask(1, d);
            cout << l << endl;
            if (l) change(1, l, l + d - 1, 2);
        } else {
            cin >> x >> d;
            change(1, x, x + d - 1, 1);
        }
    }
    return 0;
}