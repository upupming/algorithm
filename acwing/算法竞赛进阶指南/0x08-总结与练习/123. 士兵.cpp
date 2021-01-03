/*
就是 KickStart 2020 H 的第三题，中位数的应用
先把 y 移到中位数所在位置
x 方向移动后一定顺序不变
x （排好序后）不妨设移动到 a, a + 1, ..., a + (n - 1)
argmin_a {|x1 - a| + |x2 - a - 1| + |xn - a - (n-1)|}
a 就是就 x1, x2 - 1, ..., xn - (n - 1) 的中位数
*/

#include <algorithm>
#include <iostream>
using namespace std;

int n, x[10010], y[10010];
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    int ans = 0;
    sort(y, y + n);
    for (int i = 0; i < n; i++) {
        ans += abs(y[i] - y[n / 2]);
    }
    sort(x, x + n);
    for (int i = 0; i < n; i++) x[i] -= i;
    sort(x, x + n);
    for (int i = 0; i < n; i++) {
        ans += abs(x[i] - x[n / 2]);
    }
    cout << ans << endl;
    return 0;
}