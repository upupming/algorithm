/*
f[i][j] 表示一共有 i 位，且最高位是 j 的满足题目定义（不要 4 和 62）的数的个数
次高位填 k 的话，k != 4 且 jk != 62
f[i][j] += f[i-1][k]
*/
#include <iostream>
#include <vector>
using namespace std;
const int N = 15;

int f[N][10];
void init() {
    for (int i = 0; i <= 9; i++) f[1][i] = !(i == 4);
    for (int i = 2; i < N; i++) {
        for (int j = 0; j <= 9; j++) {
            if (j == 4) continue;
            for (int k = 0; k <= 9; k++) {
                if (k == 4 || (j == 6 && k == 2)) continue;
                f[i][j] += f[i - 1][k];
            }
        }
    }
}
int dp(int n) {
    if (n == 0) return 1;
    // last 表示上一位填的是什么
    int ans = 0, last = 0;
    vector<int> a;
    while (n) a.push_back(n % 10), n /= 10;
    int len = a.size() - 1;
    for (int i = len; i >= 0; i--) {
        int x = a[i];
        // 左侧分支，填 0~(x-1)
        for (int j = 0; j < x; j++) {
            // 不满足条件
            if (j == 4 || (last == 6 && j == 2)) continue;
            ans += f[i + 1][j];
        }
        // 右侧分支：填 x
        if (x == 4 || (last == 6 && x == 2)) break;
        last = x;
        // 最右侧叶子节点
        if (i == 0) ans++;
    }
    return ans;
}
int l, r;
int main() {
    init();
    while (cin >> l >> r, l, r) {
        cout << dp(r) - dp(l - 1) << endl;
    }
    return 0;
}
