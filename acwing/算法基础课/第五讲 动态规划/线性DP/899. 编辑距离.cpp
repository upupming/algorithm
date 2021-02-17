/*
把 902 多用几次就行了
时间复杂度：O(N^2*10^2) = O(10^8)
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1010;

int n, m, c, f[20][20];
char a[N][20], b[N];
int main() {
    cin >> n >> m;
    for (int k = 1; k <= n; k++) {
        scanf("%s", a[k] + 1);
    }
    while (m--) {
        scanf("%s %d", b + 1, &c);
        int tot = 0;
        for (int k = 1; k <= n; k++) {
            int n = strlen(a[k] + 1);
            int m = strlen(b + 1);
            // 初始化
            for (int i = 0; i <= m; i++) f[0][i] = i;
            for (int i = 0; i <= n; i++) f[i][0] = i;

            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    f[i][j] = min(f[i - 1][j] + 1, f[i][j - 1] + 1);
                    f[i][j] = min(f[i][j], f[i - 1][j - 1] + (a[k][i] == b[j] ? 0 : 1));
                }
            }

            if (f[n][m] <= c) tot++;
        }
        cout << tot << endl;
    }
    return 0;
}
