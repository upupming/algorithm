#include <algorithm>
#include <iostream>
using namespace std;

// 中位数选址的应用

int n, a[100010];
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    int medium = a[n / 2], ans = 0;
    for (int i = 0; i < n; i++) {
        ans += abs(a[i] - medium);
    }
    cout << ans << endl;
    return 0;
}