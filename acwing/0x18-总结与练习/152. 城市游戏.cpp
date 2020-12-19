/*
单调栈，跟「直方图中的最大矩形」类似
枚举所有的行作为底边，这一行直到上面的行作为矩形的高，那么这个问题就变成了「直方图中的最大矩形」
时间复杂度： O(NM)
*/
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1010;

char g[N][N];
// a[i][j] 表示第 i 行 j 列上方矩形高度
int n, m, stk[N], a[N][N], lft[N], rht[N];
// 利用单调栈计算 left 和 right 数组
void get(int i, int *lft) {
    // 设置哨兵
    a[i][0] = -1;
    int p = 0;
    for (int j = 1; j <= m; j++) {
        while (a[i][stk[p]] >= a[i][j]) p--;
        lft[j] = stk[p];
        stk[++p] = j;
    }
}
// 将第 1-i 行看做「直方图中的最大矩形」问题求解
int work(int i) {
    get(i, lft);
    reverse(a[i] + 1, a[i] + m + 1);
    get(i, rht);
    int ans = 0;
    for (int j = 1, k = m; j <= m; j++, k--) {
        ans = max(ans,
                  (j - lft[j] + k - rht[k] - 1) * a[i][k]);
    }
    return ans;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> g[i][j];
            if (g[i][j] == 'F') a[i][j] = a[i - 1][j] + 1;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, work(i));
    cout << 3 * ans << endl;

    return 0;
}