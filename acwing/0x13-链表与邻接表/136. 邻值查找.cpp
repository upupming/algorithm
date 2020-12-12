/*
做法 1：set + 二分查找，查找左右相邻最近的值（平衡二叉树的前驱和后继），计算完后插入 set
做法 2：链表；整体排序，建立链表，从输入的最后一个数开始，查询链表里面的前驱和后继，计算结果之后，把这个节点删除，继续计算输入的倒数第二个数，以此类推。
*/

#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

typedef pair<int, int> PII;
struct Node {
    int val, idx;
    int prev, next;
    bool operator<(const Node &b) {
        return val < b.val;
    }
} node[100010];
// b[i] = j 表示原输入序列的第 i 个数是 node[j]
int n, b[100010];
PII ans[100010];

void remove(int p) {
    node[node[p].prev].next = node[p].next;
    node[node[p].next].prev = node[p].prev;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> node[i].val, node[i].idx = i;
    }
    // 排序
    sort(node + 1, node + n + 1);
    // 建立链表连接，node[0] 和 node[n+1] 表示 head 和 tail
    for (int i = 1; i <= n + 1; i++) {
        node[i - 1].next = i;
        node[i].prev = i - 1;
        if (i >= 1 && i <= n)
            b[node[i].idx] = i;
    }
    for (int i = n; i >= 2; i--) {
        int j = b[i];
        int prev = node[j].prev, next = node[j].next;
        int prevAns = abs(node[j].val - node[prev].val);
        int nextAns = abs(node[j].val - node[next].val);
        if (prev == 0) {
            ans[i] = PII(nextAns, node[next].idx);
        } else if (next == n + 1) {
            ans[i] = PII(prevAns, node[prev].idx);
        } else {
            int best = prev;
            if (nextAns < prevAns) best = next;
            ans[i] = PII(min(nextAns, prevAns), node[best].idx);
        }
        remove(j);
    }
    for (int i = 2; i <= n; i++) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }

    return 0;
}
/*
做法 1：set + 二分查找
set<PII> s;
int main() {
    cin >> n;
    cin >> a, s.emplace(a, 1);
    for (int i = 2; i <= n; i++) {
        // cout << "i: " << i << endl;
        cin >> a;
        auto j = s.lower_bound(PII(a, i));
        if (j == s.end()) {
            // cout << "case 1" << endl;
            auto ele = *s.rbegin();
            // cout << ele.first << ", " << ele.second << endl;
            cout << abs(ele.first - a) << " " << ele.second << endl;
        } else if (j == s.begin()) {
            // cout << "case 2" << endl;
            auto ele = *s.begin();
            cout << abs(ele.first - a) << " " << ele.second << endl;
        } else {
            // cout << "case 3" << endl;
            auto ele1 = *j;
            auto ele2 = *(--j);
            int diff1 = abs(ele1.first - a), diff2 = abs(ele2.first - a);
            if (diff1 < diff2) {
                cout << diff1 << " " << ele1.second << endl;
            } else if (diff2 < diff1) {
                cout << diff2 << " " << ele2.second << endl;
            } else {
                auto &ele = ele1.first < ele2.first ? ele1 : ele2;
                // 若最小值点不唯一，则选择使 Aj 较小的那个。
                cout << diff2 << " " << ele.second << endl;
            }
        }
        s.emplace(a, i);
    }
}
*/