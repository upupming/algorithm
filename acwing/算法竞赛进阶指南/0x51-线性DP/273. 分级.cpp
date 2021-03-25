/*
f[i][j] 表示：
集合：所有给 a[1~i] 构造好了对应的 b，且最后一个数分配的是 a'[j] 的构造方案的集合（a'是a排序之后的）
属性：min abs sum of diff
转移：
枚举倒数第二个数是：
a'[1], ..., ..., a'[j]
假设倒数第二个数是 a'[k]
b1, b2, ..., b[j-2], a'[k], a'[j]
也就是：f[i-1][k] + abs(a'[j] - a[i])

同样可以用与上一题类似的优化方法，类似前缀和，之间累积算出每层循环要用的值
*/
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 2010;

int n, a[N], b[N], f[N][N];
int work() {
    for (int i = 1; i <= n; i++) b[i] = a[i];
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++) {
        int minv = 0x3f3f3f3f;
        for (int j = 1; j <= n; j++) {
            minv = min(minv, f[i - 1][j]);
            f[i][j] = minv + abs(a[i] - b[j]);
        }
    }
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        ans = min(ans, f[n][i]);
    return ans;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int ans = work();
    // 倒着的递增就是正着的递减
    reverse(a + 1, a + n + 1);
    ans = min(ans, work());
    cout << ans << endl;
    return 0;
}
