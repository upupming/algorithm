/*
f[i][j] 表示 A[1~i] 和 B[1~j] 的最短编辑距离
最后一个操作可能是：
1. 删除 A[i]，f[i-1][j] + 1
    首先把 A[1~i-1] 改成和 B[1~j] 相等，再删除 A[i]
2. 增加 A[i]，f[i][j-1] + 1
    首先把 A[1~i] 改成和 B[1~j-1] 相等，再让增加的 A[i] == B[j]
3. 修改 A[i]，f[i-1][j-1] + 1
    首先把 A[1~i-1] 改成和 B[1~j-1] 相等，再修改 A[i] 使之等于 B[j]
时间复杂度：O(NM)
*/
#include <iostream>
using namespace std;
const int N = 1010;

int n, m, f[N][N];
char a[N], b[N];
int main() {
    scanf("%d%s%d%s", &n, a + 1, &m, b + 1);

    // 初始化
    for (int i = 0; i <= m; i++) f[0][i] = i;
    for (int i = 0; i <= n; i++) f[i][0] = i;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[i][j] = min(f[i - 1][j] + 1, f[i][j - 1] + 1);
            f[i][j] = min(f[i][j], f[i - 1][j - 1] + (a[i] == b[j] ? 0 : 1));
            // cout << i << " " << j << " " << f[i][j] << endl;
        }
    }
    cout << f[n][m] << endl;
    return 0;
}
