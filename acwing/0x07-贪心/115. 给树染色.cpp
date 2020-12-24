/*
树中权值最大的点和其父节点的染色操作是连续进行的
可以将这两个点进行合并，合并之后当成一个节点，有一个 sum 和 avg，接下来可以用 avg 代表这个节点的权重，具体的证明方法就是假设 x, y 融合，再和 z 顺序进行比较，经过计算可得直接用平均值比较就行。
每次融合过程中，假设是 y 融合进他的父节点 x，那么增加的总代价为 y.sum * x.cnt，也就是说节点除了维护 sum 和 svg，还维护一个 cnt 即可
具体的做法是循环 n - 1 次，将除了根节点的所有节点融合到父节点即可（O(n)）
每次融合过程找到当前树中权值最大的节点（O(n)），进行融合操作（O(n)）

总的时间复杂度为 O(n^2)
*/
#include <iostream>
using namespace std;

struct node {
    int sum, cnt, parent;
    double avg;
};
int n, r;
node nd[1010];
int main() {
    cin >> n >> r;
    int ans = 0;
    // 注意题目的标号是 1 开始
    for (int i = 1; i <= n; i++) {
        cin >> nd[i].sum;
        nd[i].cnt = 1;
        nd[i].avg = nd[i].sum;
        ans += nd[i].sum;
    }
    int x, y;
    for (int i = 0; i < n - 1; i++) {
        cin >> x >> y;
        nd[y].parent = x;
    }
    for (int i = 0; i < n - 1; i++) {
        // 找到当前树中权值最大的节点
        double maxAvg = -1;
        int maxNode;
        for (int j = 1; j <= n; j++) {
            if (j != r && nd[j].avg > maxAvg) {
                maxAvg = nd[j].avg;
                maxNode = j;
            }
        }
        // 将这个节点合并到父节点上，产生 (父节点.cnt * 当前节点.sum) 代价
        int p = nd[maxNode].parent;
        ans += nd[p].cnt * nd[maxNode].sum;
        // 防止下次被找到成为最大节点
        nd[maxNode].avg = -1;
        nd[p].cnt += nd[maxNode].cnt;
        nd[p].sum += nd[maxNode].sum;
        nd[p].avg = (double)nd[p].sum / nd[p].cnt;
        // 把所有儿子节点的 parent 更新一下
        for (int j = 1; j <= n; j++) {
            if (nd[j].parent == maxNode)
                nd[j].parent = p;
        }
    }
    cout << ans << endl;
    return 0;
}