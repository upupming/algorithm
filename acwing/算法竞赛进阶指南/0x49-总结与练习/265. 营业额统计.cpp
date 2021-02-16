/*
动态维护 treap，每次找 ai 的前驱 prev 和后继 next 即可
更新 ans += min(ai - prev, next - ai)

原有的找前驱和后继函数如果存在这个数，是不会返回这个数本身的，而是最近的值，因此需要改造一下，如果有相等的，直接返回这个值，这样 diff = 0

*/
#include <iostream>
using namespace std;
const int N = 4e4 + 10;

// 数组模拟链表
struct Treap {
    // 左右子节点在数组中的下标
    int l, r;
    // 节点的关键码、权值
    int val, dat;
    // 副本数、子树大小
    int cnt, size;
} a[N];
int tot, root, INF = 0x7fffffff;

int New(int val) {
    a[++tot].val = val;
    // 随机初始化权值
    a[tot].dat = rand();
    a[tot].cnt = a[tot].size = 1;
    return tot;
}

// 类似线段树自下往上的更新过程
void Update(int p) {
    a[p].size = a[a[p].l].size + a[a[p].r].size + a[p].cnt;
}

void Build() {
    // 为避免越界，减少边界情况特殊判断，加入哨兵
    New(-INF), New(INF);
    root = 1, a[1].r = 2;
    Update(root);
}

// 把 p 的左子节点绕着 p 向右旋转，注意 p 是引用
void zig(int &p) {
    int q = a[p].l;
    a[p].l = a[q].r, a[q].r = p, p = q;
    Update(a[p].r), Update(p);
}
// 把 p 的右子节点绕着 p 向左旋转，注意 p 是引用
void zag(int &p) {
    int q = a[p].r;
    a[p].r = a[q].l, a[q].l = p, p = q;
    Update(a[p].l), Update(p);
}

// 注意 p 是引用
void Insert(int &p, int val) {
    if (p == 0) {
        p = New(val);
        return;
    }
    // 如果之前已经有相同关键码的节点，只需要 cnt++ 即可
    if (val == a[p].val) {
        a[p].cnt++, Update(p);
        return;
    }
    // 在左子树中插入
    if (val < a[p].val) {
        Insert(a[p].l, val);
        // 不满足堆性质，右旋
        if (a[p].dat < a[a[p].l].dat) zig(p);
    }
    // 在右子树中插入
    else {
        Insert(a[p].r, val);
        // 不满足堆性质，左旋
        if (a[p].dat < a[a[p].r].dat) zag(p);
    }
    Update(p);
}

int GetPre(int val) {
    // a[1].val = -INF
    int ans = 1;
    int p = root;
    // 一直循环直到找到一个关键码为 val 的节点，找到之后会直接 break
    // 找不到也没关系，已经经过的节点中一定包含答案，ans 即为所求
    while (p) {
        if (val == a[p].val) return val;
        // 节点 p 是小于 val 的，并且相比 ans 离 val 更近，更新 ans
        if (a[p].val < val && a[p].val > a[ans].val) ans = p;
        // 根据 val 情况往左或者往右走
        p = val < a[p].val ? a[p].l : a[p].r;
    }
    return a[ans].val;
}

int GetNext(int val) {
    // a[2].val == INF
    int ans = 2;
    int p = root;
    while (p) {
        if (val == a[p].val) return val;
        if (a[p].val > val && a[p].val < a[ans].val) ans = p;
        p = val < a[p].val ? a[p].l : a[p].r;
    }
    return a[ans].val;
}

int n, x, ans;
int main() {
    cin >> n;
    Build();
    for (int i = 1; i <= n; i++) {
        cin >> x;
        if (i == 1)
            ans += x;

        else {
            int y = INF;
            if (GetPre(x) != -INF) y = min(y, x - GetPre(x));
            if (GetNext(x) != INF) y = min(y, GetNext(x) - x);
            // cout << i << " " << y << endl;
            ans += y;
        }

        Insert(root, x);
    }
    cout << ans << endl;
    return 0;
}