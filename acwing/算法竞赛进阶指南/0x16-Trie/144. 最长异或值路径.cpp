/*
先 DFS 求出根节点到每个点 x 的路径上所有边权的异或值 D(x)
两个点 x 和 y 之间的所有边的边权异或值就是 D(x) xor D(y)
问题就变成了求从 D(1) 到 D(N) 选两个数，异或值最大，就是上一题，用 Trie 求解即可
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 10, M = 32 * N;

int n, u, v, w;
// 数组模拟邻接表常用形式
int head[N], ver[2 * N], edge[2 * N], Next[2 * N], tot;
int d[N];
int trie[M][2], p, q, tsize = 1;

// 加入有向边 (x, y)，权值为 z
void add(int x, int y, int z) {
    // 真实数据
    ver[tot] = y, edge[tot] = z;
    // 在表头 x 处插入
    Next[tot] = head[x], head[x] = tot++;
}
// father 防止回溯，sum 记下之前的异或总和
void dfs(int x, int father, int sum) {
    // cout << x << " " << father << " " << sum << endl;
    d[x] = sum;
    // 遍历 u 的所有边
    for (int i = head[x]; ~i; i = Next[i]) {
        int y = ver[i], z = edge[i];
        if (y != father) dfs(y, x, sum ^ z);
    }
}
// 查询某个数的最大异或值
int query(int a) {
    p = q = 1;
    int ans = 0;
    for (int i = 31; i >= 0; i--) {
        int j = a >> i & 1;
        // cout << a << " " << i << " " << j << endl;
        if (trie[p][j] == 0) trie[p][j] = ++tsize;
        p = trie[p][j];
        // 寻找匹配，能够匹配一个不同的位的话
        if (trie[q][!j]) {
            ans |= 1 << i;
            q = trie[q][!j];
        } else {
            q = trie[q][j];
        }
    }
    return ans;
}
int main() {
    cin >> n;
    memset(head, 0xff, sizeof(head));
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    dfs(0, -1, 0);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        // cout << d[i] << endl;
        ans = max(ans, query(d[i]));
    }
    cout << ans << endl;
    return 0;
}
