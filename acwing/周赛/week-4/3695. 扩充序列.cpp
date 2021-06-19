#include <iostream>
using namespace std;
typedef long long LL;
LL n, k;
LL dp(LL n, LL k) {
    LL len = (1ll << n) - 1;
    LL mid = (len + 1) / 2;
    // cout << n << " " << k << " " << mid << endl;
    if (k == mid)
        return n;
    else if (k < mid) {
        return dp(n - 1, k);
    }
    return dp(n - 1, k - mid);
}
int main() {
    cin >> n >> k;
    cout << dp(n, k);
    return 0;
}
