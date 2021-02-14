/*
二分，计算转判定
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;

int n, h[N];
bool valid(int e) {
    // 模拟跳跃过程
    for (int i = 1; i <= n; i++) {
        if (h[i] > e)
            e -= h[i] - e;
        else
            e += e - h[i];
        // 提前返回，否则可能 overflow
        if (e > 1e5) return true;
        if (e < 0) return false;
    }
    return true;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];
    int l = 1, r = 1e5;
    while (l < r) {
        int mid = l + r >> 1;
        // cout << l << " " << r << " " << mid << endl;
        if (valid(mid))
            r = mid;
        else
            l = mid + 1;
    }
    cout << l << endl;
    return 0;
}