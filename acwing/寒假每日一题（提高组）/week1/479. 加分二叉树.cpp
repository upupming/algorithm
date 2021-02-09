/*
区间 dp：
f[i][j] 表示：
集合：由 [i, j] 区间的所有节点构成的二叉树的集合
属性：最大值
状态计算：
f[i][j] = f[i][k-1] * f[k+1][j] + w[k]
初始值 f[i][i] = w[k]，循环过程中每一层计算长度为 len 的区间

如何存储前序遍历：
g[i][j] 表示取得最大值的下标 k，k 就是从 i 到 j 的子树的根节点
递归输出即可
字典序最小：只需要保证 k 是第一个最大值即可，递归过程会自动保证总的字典序最小
*/
#include <iostream>
using namespace std;
const int N = 35;

int n;
int w[N], f[N][N], g[N][N];
void dfs(int l, int r) {
    if (l > r) return;
    cout << g[l][r] << " ";
    dfs(l, g[l][r] - 1);
    dfs(g[l][r] + 1, r);
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i];

    for (int len = 1; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            // 初始条件
            if (len == 1)
                f[i][j] = w[i], g[i][j] = i;
            else {
                for (int k = i; k <= j; k++) {
                    int left = k == i ? 1 : f[i][k - 1];
                    int right = k == j ? 1 : f[k + 1][j];
                    int score = left * right + w[k];

                    if (score > f[i][j]) {
                        f[i][j] = score;
                        g[i][j] = k;
                    }
                }
            }
        }
    }
    cout << f[1][n] << endl;
    dfs(1, n);
    return 0;
}