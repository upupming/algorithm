/*
排序后，从中间进行划分即可
*/
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1e5 + 10;

int n, a[N], sum[N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);

    for (int i = 1; i <= n; i++) sum[i] = a[i] + sum[i - 1];

    // a[1..n/2], 剩余部分
    cout << n % 2 << " ";
    cout << (sum[n] - sum[n / 2]) - (sum[n / 2]) << endl;
    return 0;
}