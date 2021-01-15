/*
二分查找最大的正方形边长即可
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;

int n, k, h[N], w[N];
bool valid(int a) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += (h[i] / a) * (w[i] / a);
    }
    return cnt >= k;
}
int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> h[i] >> w[i];
    int l = 0, r = 1e5;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (valid(mid))
            l = mid;
        else
            r = mid - 1;
    }
    cout << l << endl;
    return 0;
}