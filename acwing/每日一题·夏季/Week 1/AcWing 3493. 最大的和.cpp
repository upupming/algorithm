/*
枚举所有可能的区间 [l, l+k-1]，将这个区间内所有的元素都置为可选
可以用滑动窗口，不需要额外的 sum 空间
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
typedef long long LL;

int a[N], n, k, st[N];
LL sum[N], st_sum[N];
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> st[i];
        st_sum[i] = st_sum[i - 1] + st[i] * a[i];
    }
    LL ans = 0;
    for (int l = 1; l + k - 1 <= n; l++) {
        int r = l + k - 1;
        ans = max(ans,
                  // [l, r]
                  sum[r] - sum[l - 1] +
                      //   [1, l-1]
                      st_sum[l - 1] +
                      //   [r+1, n]
                      st_sum[n] - st_sum[r]);
    }
    cout << ans << endl;
    return 0;
}
