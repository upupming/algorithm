#include <algorithm>
#include <iostream>

using namespace std;

int t, n, h[200];

int solve() {
    int ans = 0;
    for (int i = 1; i < n - 1; i++) {
        if (h[i] > h[i - 1] && h[i] > h[i + 1]) {
            ans++;
        }
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> h[i];
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}