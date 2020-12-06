/*
环形均分纸牌问题，选取中位数 s[k] 求一下差值之和即可
*/

#include <algorithm>
#include <iostream>
using namespace std;

int n, a[1000010];
long long avg;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], avg += a[i];
    avg /= n;
    // 前缀和
    for (int i = 1; i <= n; i++) a[i] += a[i - 1] - avg;
    // 找中位数
    sort(a + 1, a + n + 1);
    int mid = (n + 1) / 2;
    long long ans = 0;
    for (int i = 1; i <= n; i++) ans += abs(a[i] - a[mid]);
    cout << ans << endl;
}
