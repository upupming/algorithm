/*
dp[i][j] 表示 A[1~i] 与 B[1~j] 的最长公共子序列长度，时间复杂度 O(NM)

如果有一个字符串没有重复字符，可以有 O(NlogN) 的做法，具体看 LeetCode 5644
*/
#include <iostream>
using namespace std;
const int N = 1010;

int f[N][N], n, m;
char s[N], t[N];
int main() {
    cin >> n >> m;
    scanf("%s%s", s + 1, t + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[i][j] = max(f[i][j - 1], f[i - 1][j]);
            if (s[i] == t[j])
                f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
        }
    }
    cout << f[n][m] << endl;
    return 0;
}
