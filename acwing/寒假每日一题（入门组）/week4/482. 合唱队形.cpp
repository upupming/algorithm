/*
f[i] 表示结尾下标为 i 的最长上升子序列长度
    f[i] = max(f[k] + 1), a[k] < a[i]
g[i] 表示开始下标为 i 的最长下降子序列长度

初始条件 f[i] = 1
*/
#include <iostream>
using namespace std;
const int N = 110;

int n, a[N], f[N], g[N], ans;
int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        f[i] = 1;
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) f[i] = max(f[i], f[j] + 1);
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        g[i] = 1;
        for (int j = n - 1; j > i; j--) {
            if (a[i] > a[j]) g[i] = max(g[i], g[j] + 1);
        }
        ans = max(ans, f[i] + g[i] - 1);
    }

    cout << n - ans << endl;
    return 0;
}