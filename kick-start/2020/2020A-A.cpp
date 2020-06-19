#include <algorithm>
#include <iostream>

using namespace std;

int t, n, a[100005], b;

int solve() {
    sort(a, a + n);
    int i = 0;
    for (; i < n; i++) {
        if (i != 0) {
            a[i] = a[i - 1] + a[i];
        }
        if (a[i] > b) break;
    }
    return i;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> b;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}