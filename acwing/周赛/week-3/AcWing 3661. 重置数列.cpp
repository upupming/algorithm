#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 10;

int t, n, k, a[N], b[N];
int main() {
    cin.sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> a[i];
        int ans = n;
        for (int d = 1; d <= 100; d++) {
            int tmp = 0;
            for (int i = 1; i <= n; i++) {
                if (a[i] == d) continue;
                tmp++;
                int j = min(i + k - 1, n);
                i = j;
            }
            ans = min(ans, tmp);
        }
        cout << ans << endl;
    }
    return 0;
}
