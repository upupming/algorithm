/*
前置知识: 单调栈、直方图中的最大矩形、城市游戏
将 (x_i, y_i) 改为 0 之后，只包含 1 的子矩阵一定能被 (x_i, y_i) 的上、下、左、右部分四者之一完全包含（反证，否则的话就会包含 x_i, y_i 点了）
利用前缀和，求一下以每一行结束，这一行及以上的子矩阵的面积最大值，存入 U 数组，其他 3 个方向同理即可
预处理：O(4 * N^2)
查询: O(Q)
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 2010;

int n, m, q, g[N][N], U[N], D[N], L[N], R[N];
int lft[N], rht[N], stk[N], tt;
string s[N];
int calc(int h[], int n) {
    // 哨兵
    h[0] = -1, h[n + 1] = -1;
    tt = 0;
    stk[++tt] = 0;
    for (int i = 1; i <= n; i++) {
        while (h[stk[tt]] >= h[i]) tt--;
        lft[i] = stk[tt];
        stk[++tt] = i;
    }
    tt = 0;
    stk[++tt] = n + 1;
    for (int i = n; i >= 1; i--) {
        while (h[stk[tt]] >= h[i]) tt--;
        rht[i] = stk[tt];
        stk[++tt] = i;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int width = i - lft[i] + rht[i] - i - 1;
        ans = max(ans, width * h[i]);
    }
    return ans;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] = ' ' + s[i];
    }

    // 其实 g 可以用滚动数组，继续降低空间复杂度
    // 从上到下运行「城市游戏」
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == '1')
                g[i][j] = g[i - 1][j] + 1;
            else
                g[i][j] = 0;
        }
        U[i] = max(U[i - 1], calc(g[i], m));
    }
    // 从下到上运行「城市游戏」
    memset(g, 0, sizeof g);
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == '1')
                g[i][j] = g[i + 1][j] + 1;
            else
                g[i][j] = 0;
        }
        D[i] = max(D[i + 1], calc(g[i], m));
    }
    // 从左到右运行「城市游戏」
    memset(g, 0, sizeof g);
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            if (s[i][j] == '1')
                g[j][i] = g[j - 1][i] + 1;
            else
                g[j][i] = 0;
        }
        L[j] = max(L[j - 1], calc(g[j], n));
    }
    // 从右到左运行「城市游戏」
    memset(g, 0, sizeof g);
    for (int j = m; j >= 1; j--) {
        for (int i = 1; i <= n; i++) {
            if (s[i][j] == '1')
                g[j][i] = g[j + 1][i] + 1;
            else
                g[j][i] = 0;
        }
        R[j] = max(R[j + 1], calc(g[j], n));
    }

    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        x++, y++;
        cout << max(
                    max(U[x - 1], D[x + 1]),
                    max(L[y - 1], R[y + 1]))
             << endl;
    }

    return 0;
}
