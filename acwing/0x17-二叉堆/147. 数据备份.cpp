/*
先确定选哪 2K 个点，然后确定这 2K 个点的配对方案。
确定了 2K 个点之后，他们的配对方案一定是从左到右每两个作为一对，可以用反证法证明。
如何选这 2K 个点呢？我只想到了暴力枚举的方法。
书上则又提出了一点，先求出相邻办公楼之间的距离 D[1-N-1]，将问题转化为从数列 D 中选择不超过 K 个数，使他们的和最小，并且相邻的两个数不能同时被选。

优先队列有删除指定元素的需求的时候，可以转换为使用 set，或者用一个标记数组，pop 的时候判断一下是否已经被删除了
*/
#include <iostream>
#include <queue>
using namespace std;
const int N = 2e5 + 20;

// 链表节点
struct LNode {
    int val;
    int prev, next;
} l[N];
// 堆节点
struct HNode {
    int lNodeIdx;
    // 注意是最小堆
    bool operator<(const HNode &b) const {
        return l[lNodeIdx].val > l[b.lNodeIdx].val;
    }
};
int n, k, s[N], del[N];
priority_queue<HNode> pq;

void deleteNode(int i) {
    l[l[i].prev].next = l[i].next;
    l[l[i].next].prev = l[i].prev;
}

int main() {
    cin >> n >> k;
    // 哨兵，要满足 l[pPrev].val + l[pNext].val - l[p].val 不溢出，也就是得到一个很大的数入堆，之后不可能被选中
    l[0].val = l[n].val = 0x3f3f3f3f;
    l[0].next = 1, l[n].prev = n - 1;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        if (i >= 1) {
            l[i].val = s[i] - s[i - 1];
            l[i].prev = i - 1;  // 0 表示 head
            l[i].next = i + 1;  // n 表示 tail
            // cout << i << ", " << l[i].val << endl;
            HNode hNode;
            hNode.lNodeIdx = i;
            pq.push(hNode);
            // cout << pq.top().lNodeIdx << ": " << l[pq.top().lNodeIdx].val << endl;
        }
    }

    long long ans = 0;
    // 重复 k 次选择组合
    for (int i = 0; i < k; i++) {
        while (del[pq.top().lNodeIdx]) pq.pop();
        int p = pq.top().lNodeIdx;
        pq.pop();
        ans += l[p].val;
        int pPrev = l[p].prev, pNext = l[p].next;
        l[p].val = l[pPrev].val + l[pNext].val - l[p].val;
        deleteNode(pPrev), deleteNode(pNext);

        // 从堆中删除节点 pPrev 和 pNext
        del[pPrev] = del[pNext] = 1;
        // 构建新节点并入堆
        HNode hNode1;
        hNode1.lNodeIdx = p;
        pq.push(hNode1);
    }
    cout << ans << endl;
    return 0;
}