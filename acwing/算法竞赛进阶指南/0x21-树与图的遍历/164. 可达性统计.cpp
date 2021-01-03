/*
f(x) 表示从点 x 出发，能够到达的点的集合，可以用 bitset 进行状态压缩，每一位表示一个点的存在与否
f(x) = x 并上所有从 x 出发可以到达的点 y
先运行一遍拓扑排序，然后按照拓扑排序倒序遍历所有的点，每次求可以到达的点的 f 的并集，加上这个点，即可得到这个点的 f；有点类似dp的思想
时间复杂度：如果 f 状态用 int 来存，每个 f 约需要 N/32 个 int，需要遍历到所有的点和边 N+M，总时间复杂度为 O(N(N+M)/32)
*/
#include <bitset>
#include <cassert>
#include <iostream>
#include <queue>
using namespace std;
const int N = 3e4 + 10;

int a[N], tot, ver[N], Next[N], head[N], deg[N], cnt, n, m;
// 3e4^2 bits = 112.5 MB，存储空间 258MB 刚好够用
bitset<N> bs[N];
void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
    deg[y]++;
}
// 拓扑排序模板
void topsort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) q.push(i);
    }
    while (q.size()) {
        int x = q.front();
        q.pop();
        a[++cnt] = x;
        for (int i = head[x]; i; i = Next[i]) {
            int y = ver[i];
            if (--deg[y] == 0) q.push(y);
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        add(x, y);
    }
    topsort();
    assert(cnt == n);
    // 按照拓扑排序反向遍历（因为最后一个没有出边，作为 base case）
    for (int i = n; i >= 1; i--) {
        int x = a[i];
        // 首先肯定包含自身
        // 坑点：bitset 类型不能直接和数字进行或操作（但是不报语法错误），写成 bs[x] |= 1 << x 是不对的
        bs[x][x] = 1;
        // 对于从 x 出发的所有边的终点 y，f(x) 包含 f(y)
        for (int j = head[x]; j; j = Next[j]) {
            int y = ver[j];
            bs[x] |= bs[y];
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << bs[i].count() << endl;
    }
    return 0;
}