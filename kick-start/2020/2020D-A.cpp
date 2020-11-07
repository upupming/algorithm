#include <algorithm>
#include <iostream>

using namespace std;

int t, n;

int solve() {
    return 0;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        int last = -1, cur, MAX = -1, ans = 0;
        bool counting = true;
        for (int i = 0; i < n; i++) {
            cin >> cur;

            if (cur < last) {
                // cout << last << endl;
                ans += counting;
                // restart count
                counting = false;
            } else if (cur == last) {
                counting = false;
            } else {
                if (cur > MAX) {
                    counting = true;
                    if (i == n - 1) ans++;
                }
            }

            MAX = max(MAX, cur);
            last = cur;
        }

        printf("Case #%d: %d\n", i, ans);
    }
    return 0;
}