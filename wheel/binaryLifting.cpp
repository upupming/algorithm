// https://www.geeksforgeeks.org/lca-in-a-tree-using-binary-lifting-technique/
// https://zhuanlan.zhihu.com/p/113042043

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

// Number of nodes
const int n = 9;
const int m = (int)ceil(log2(n));
// vector to store tree
vector<int> g[n + 1];
// memo[i][j] 表示节点 i 的第 2^j 个父节点
int **fatherTable = new int *[n + 1];
// Stores the level of each node
int *lev = new int[n + 1];

// O(n log n) 预处理
// 0 dummy node: 不存在在原树里面，虚拟出来作为所有节点父节点的节点
// 因为 fatherTable 初始化为 0，所以 fatherTable[0][0] = 0
void dfs(int u, int father = 0) {
    // ft[u][0] 就是 u 的父亲节点
    fatherTable[u][0] = father;
    for (int i = 1; i <= m; i++) {
        fatherTable[u][i] = fatherTable[fatherTable[u][i - 1]][i - 1];
    }
    lev[u] = lev[father] + 1;
    for (auto v : g[u]) {
        if (v != father) {
            dfs(v, u);
        }
    }
}

// O(log n) 查询
int lca(int a, int b) {
    // 不妨设 lev[a] <= lev[b]
    if (lev[a] > lev[b]) swap(a, b);
    while (lev[a] != lev[b]) {
        // 例如，a和b本来相差22的深度，现在b不用往上爬22次，只需要依次跳16、4、2个单位，3次便能达到与a相同的距离。
        b = fatherTable[b][(int)floor(log2(lev[b] - lev[a]))];
    }
    if (a == b) return a;
    // 说来也简单，从可能跳的最大步数Log2[dep[a]]（这样至多跳到根节点，不会越界）开始，不断减半步数（不用多次循环）：
    for (int k = m; k >= 0; k--) {
        if (fatherTable[a][k] != fatherTable[b][k]) {
            a = fatherTable[a][k];
            b = fatherTable[b][k];
        }
    }
    return fatherTable[a][0];
}

int main() {
    for (int i = 0; i < n + 1; i++) {
        fatherTable[i] = new int[m + 1];
    }

    // Add edges
    g[1].push_back(2);
    g[2].push_back(1);
    g[1].push_back(3);
    g[3].push_back(1);
    g[1].push_back(4);
    g[4].push_back(1);
    g[2].push_back(5);
    g[5].push_back(2);
    g[3].push_back(6);
    g[6].push_back(3);
    g[3].push_back(7);
    g[7].push_back(3);
    g[3].push_back(8);
    g[8].push_back(3);
    g[4].push_back(9);
    g[9].push_back(4);

    // dfs(1);
    dfs(4);

    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            cout << "The LCA of " << i << " and " << j << " is " << lca(i, j) << endl;
        }
        cout << endl;
    }

    return 0;
}