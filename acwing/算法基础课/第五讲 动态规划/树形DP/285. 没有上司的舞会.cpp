/*
f[i][0]: 不选根节点 i，整个子树的最大值
f[i][1]: 选根节点 i，整个子树的最大值
dfs 一下就可以得到结果
*/
#include <iostream>
using namespace std;
const int N = 6010, M = 6010;

int head[N], ver[M], Next[M], tot;
// 没有父节点的就是 root
int n, h[N], has_fa[N], f[N][2];
void add(int x, int y) {
    ver[++tot] = y;
    Next[tot] = head[x], head[x] = tot;
}
void dfs(int x) {
    f[x][1] = h[x];
    for (int i = head[x]; i; i = Next[i]) {
        int y = ver[i];
        dfs(y);
        // 选 x 的时候，y 一定不能选
        f[x][1] += f[y][0];
        // 不选 x 的时候，y 选不选都可
        f[x][0] += max(f[y][0], f[y][1]);
    }
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];
    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        cin >> x >> y;
        add(y, x), has_fa[x] = 1;
    }
    int root;
    for (int i = 1; i <= n; i++) {
        if (!has_fa[i]) {
            root = i;
            break;
        }
    }
    dfs(root);
    cout << max(f[root][0], f[root][1]) << endl;
    return 0;
}
