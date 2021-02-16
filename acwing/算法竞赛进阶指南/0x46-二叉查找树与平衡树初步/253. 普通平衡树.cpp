/*
在原有 treap 平衡树的基础上维护副本数 cnt 和以该节点为根的子树大小 size，计算过程参考代码即可。
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;

// 数组模拟链表
struct Treap {
    // 左右子节点在数组中的下标
    int l, r;
    // 节点的关键码、权值
    int val, dat;
    // 副本数、子树大小
    int cnt, size;
} a[N];
int tot, root, n, INF = 0x7fffffff;

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
        if (val == a[p].val) {
            if (a[p].l > 0) {
                p = a[p].l;
                // 左子树一直往右走
                while (a[p].r > 0) p = a[p].r;
                ans = p;
            }
            // 检索成功之后会 break 掉
            break;
        }
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
        if (val == a[p].val) {
            if (a[p].r > 0) {
                p = a[p].r;
                // 右子树一直往左走
                while (a[p].l > 0) p = a[p].l;
                ans = p;
            }
            break;
        }
        if (a[p].val > val && a[p].val < a[ans].val) ans = p;
        p = val < a[p].val ? a[p].l : a[p].r;
    }
    return a[ans].val;
}

// 注意 p 是引用
void Remove(int &p, int val) {
    if (p == 0) return;
    // 检索到了 val
    if (val == a[p].val) {
        // 有重复，减少副本次数即可
        if (a[p].cnt > 1) {
            a[p].cnt--, Update(p);
            return;
        }
        // 不是叶子节点，向下旋转，旋转成叶节点之后，直接删除即可
        if (a[p].l || a[p].r) {
            if (a[p].r == 0 || a[a[p].l].dat > a[a[p].r].dat) {
                zig(p), Remove(a[p].r, val);
            } else {
                zag(p), Remove(a[p].l, val);
            }
            Update(p);
        } else {
            // 叶子节点，删除，注意 p 是引用
            p = 0;
        }
        return;
    }
    // 根据 val 情况往左或者往右走
    val < a[p].val ? Remove(a[p].l, val) : Remove(a[p].r, val);
    Update(p);
}

// --- 在 treap 基础上扩展的两个函数（前面的都可以通过 multiset 实现）
int GetRankByVal(int p, int val) {
    if (p == 0) return 0;
    // 就是当前节点
    if (val == a[p].val) return a[a[p].l].size + 1;
    // 小于当前节点，在左子树中
    if (val < a[p].val) return GetRankByVal(a[p].l, val);
    // 大于当前节点，在右子树中
    return GetRankByVal(a[p].r, val) + a[a[p].l].size + a[p].cnt;
}
int GetValByRank(int p, int rank) {
    if (p == 0) return INF;
    // 在左子树中
    if (a[a[p].l].size >= rank) return GetValByRank(a[p].l, rank);
    // 在当前节点中
    if (a[a[p].l].size + a[p].cnt >= rank) return a[p].val;
    // 在右子树中
    return GetValByRank(a[p].r, rank - a[a[p].l].size - a[p].cnt);
}

int main() {
    Build();
    cin >> n;
    while (n--) {
        int op, x;
        cin >> op >> x;
        switch (op) {
            case 1:
                Insert(root, x);
                break;
            case 2:
                Remove(root, x);
                break;
            case 3:
                // 减 1 是消去负无穷哨兵的影响
                cout << GetRankByVal(root, x) - 1 << endl;
                break;
            case 4:
                // 加 1 是消去负无穷哨兵的影响
                cout << GetValByRank(root, x + 1) << endl;
                break;
            case 5:
                cout << GetPre(x) << endl;
                break;
            case 6:
                cout << GetNext(x) << endl;
                break;
        }
    }
    return 0;
}