/*
为了支持「区间修改」，线段树需要使用延迟标记，将区间修改的复杂度从 O(N) 降为 O(log N)（每次只需要真正修改那些直接划分成的 O(log N) 个节点，其他的修改延迟到「在后续操作中递归进入它的父节点时」再执行）
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;

// 注意：有延迟标记的节点，本身已经完成了数据更新，只是没有传递给子节点
struct SegmentTree {
    int l, r;
    long long dat, flag;
#define l(x) tree[x].l
#define r(x) tree[x].r
#define dat(x) tree[x].dat
#define flag(x) tree[x].flag
} tree[N * 4];
int a[N], n, m;

void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    if (l == r) {
        dat(p) = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    dat(p) = dat(2 * p) + dat(2 * p + 1);
}
void spread(int p) {
    // 节点 p 有延迟标记的话
    if (flag(p)) {
        // 更新左子节点信息，延迟值 * 区间长度等于节点的增加量
        dat(2 * p) += flag(p) * (r(2 * p) - l(2 * p) + 1);
        // 更新右子节点信息
        dat(2 * p + 1) += flag(p) * (r(2 * p + 1) - l(2 * p + 1) + 1);
        // 给左子节点打延迟标记
        flag(2 * p) += flag(p);
        // 给右子节点打延迟标记
        flag(2 * p + 1) += flag(p);
        // 清除 p 的标记
        flag(p) = 0;
    }
}

void change(int p, int l, int r, int d) {
    // 完全覆盖
    if (l <= l(p) && r >= r(p)) {
        // 更新节点信息，每个节点增加量 d * 区间长度 = 节点增加量
        dat(p) += (long long)d * (r(p) - l(p) + 1);
        // 给节点打延迟标记
        flag(p) += d;
        return;
    }
    // 因为即将访问下面的节点了，必须先下传延迟标记
    spread(p);
    int mid = (l(p) + r(p)) >> 1;
    // 和左子节点有相交部分
    if (l <= mid) change(2 * p, l, r, d);
    // 和右子节点有相交部分
    if (r >= mid + 1) change(2 * p + 1, l, r, d);
    dat(p) = dat(2 * p) + dat(2 * p + 1);
}

long long ask(int p, int l, int r) {
    if (l <= l(p) && r >= r(p)) return dat(p);
    // 因为即将访问下面的节点了，必须先下传延迟标记
    spread(p);
    int mid = l(p) + r(p) >> 1;
    long long val = 0;
    if (l <= mid) val += ask(2 * p, l, r);
    if (r >= mid + 1) val += ask(2 * p + 1, l, r);
    return val;
}

string s;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    while (m--) {
        int l, r, d;
        cin >> s;
        if (s[0] == 'Q') {
            cin >> l >> r;
            cout << ask(1, l, r) << endl;
        } else {
            cin >> l >> r >> d;
            change(1, l, r, d);
        }
    }
    return 0;
}