/*
做法 1：字符串哈希+二分
做法 2：KMP
*/
#include <iostream>
using namespace std;
const int P = 131, N = 2e5 + 10;

typedef unsigned long long ULL;

// ans[x] = y 表示
// 有 y 个位置，满足“字符串A从该位置开始的后缀子串”与B匹配的长度恰好为x
int n, m, q, x, ans[N];
ULL f[N], p[N], g[N];
char a[N], b[N];
bool valid(int l, int r) {
    return (f[r] - f[l - 1] * p[r - l + 1]) == g[r - l + 1];
}
int main() {
    cin >> n >> m >> q;
    scanf("%s", a + 1);
    scanf("%s", b + 1);

    p[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1] * P + a[i] - '0' + 1;
        p[i] = p[i - 1] * P;
    }
    for (int i = 1; i <= m; i++) {
        g[i] = g[i - 1] * P + b[i] - '0' + 1;
        p[i] = p[i - 1] * P;
    }

    // 枚举所有起始点
    for (int i = 1; i <= n; i++) {
        // 二分终止点，注意 l = r - 1 表示匹配长度恰好为 0 的情况
        int l = i - 1, r = n;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (valid(i, mid))
                l = mid;
            else
                r = mid - 1;
        }
        ans[l - i + 1]++;
    }

    while (q--) {
        cin >> x;
        cout << ans[x] << endl;
    }

    return 0;
}