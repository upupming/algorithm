/*
按照等式从后往前搜，枚举所有满足情况的分配即可，dfs 的时候需要传一个进位给下一层
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 26;

// n 表示进制，题目给定了式子长度也是 n
int ans[N], n, used[N], b[3][N];
string a[3];
// 这个优化非常重要，不然过不了
bool check(int k) {
    for (int bit_k = n - 1; bit_k >= k; bit_k--) {
        int x1 = b[0][bit_k], a1 = ans[x1];
        int x2 = b[1][bit_k], a2 = ans[x2];
        int x3 = b[2][bit_k], a3 = ans[x3];
        // 如果已经确定，提前剪枝
        if (a1 != -1 && a2 != -1 && a3 != -1 &&
            (a1 + a2) % n != a3 &&
            (a1 + a2 + 1) % n != a3) return false;
    }
    return true;
}
// 当前搜索到第 bit_k 位，来自第 k - 1 位的进位为 r
// g = 0, 1, 2 表示正在分配第 g 行
bool dfs(int bit_k, int r, int g) {
    if (bit_k == n) return true;

    int x = b[g][bit_k];
    if (!check(bit_k)) return false;

    int x1 = b[0][bit_k], a1 = ans[x1];
    int x2 = b[1][bit_k], a2 = ans[x2];
    int sum = ans[x1] + ans[x2] + r;

    // 如果之前 x 已经被更低的位确定了
    if (ans[x] != -1) {
        if (g == 2) {
            if (sum % n == ans[x]) {
                if (dfs(bit_k + 1, sum / n, 0)) return true;
            }
        } else {
            if (dfs(bit_k, r, g + 1)) return true;
        }
    }
    // 枚举所有的分配情况
    else {
        // 优化：当 g == 2 时，x 的选择只能是 sum % n
        if (g == 2) {
            int i = sum % n;
            if (!used[i]) {
                used[i] = true;
                ans[x] = i;

                if (dfs(bit_k + 1, sum / n, 0)) return true;

                ans[x] = -1;
                used[i] = false;
            }
        } else
            for (int i = n - 1; i >= 0; i--) {
                if (used[i]) continue;
                used[i] = true;
                ans[x] = i;

                if (dfs(bit_k, r, g + 1)) return true;

                ans[x] = -1;
                used[i] = false;
            }
    }

    return false;
}
int main() {
    cin >> n;
    cin >> a[0] >> a[1] >> a[2];
    for (int g = 0; g < 3; g++)
        for (int k = 0; k < n; k++) {
            b[g][k] = a[g][n - 1 - k] - 'A';
        }
    memset(ans, 0xff, sizeof(ans));
    dfs(0, 0, 0);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
}