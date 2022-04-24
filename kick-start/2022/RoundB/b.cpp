#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

typedef long long LL;
int t;
LL a;
string s;
#define N 3000000
LL b[N];
int n;

int solve() {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a % b[i] == 0) ans++;
        if (b[i] >= a) break;
    }
    return ans;
}

int main() {
    cin >> t;
    for (LL x = 1;; x++) {
        auto s = to_string(x), t = to_string(x);
        reverse(t.begin(), t.end());
        LL y = atoll((s + t).c_str());
        b[n++] = y;
        for (int i = 0; i <= 9; i++) {
            LL y = atoll((s + to_string(i) + t).c_str());
            b[n++] = y;
        }
        if (x <= 9) {
            b[n++] = x;
        }
        if (y >= 2e10) break;
    }
    sort(b, b + n);
    for (int i = 1; i <= t; i++) {
        cin >> a;
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
