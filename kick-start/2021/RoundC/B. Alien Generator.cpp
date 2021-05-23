#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
typedef long long LL;

using namespace std;

int t;
LL g;

LL solve() {
    LL ans = 0;
    double delta = sqrt(1 + 8 * g);
    LL start = floor((1 - delta) / 2), end = ceil((1 + delta) / 2);
    for (auto x = max(start, 1ll); x <= end; x++) {
        auto above = (2 * g - x * x + x), under = (2 * x);
        if (above % under == 0 && above / under > 0) {
            ans++;
        }
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> g;
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
