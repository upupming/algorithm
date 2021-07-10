#include <iostream>
using namespace std;
const int N = 1e5 + 10;
typedef long long LL;

LL f[N][3];

int t, n, k;
string ans;
int main() {
    cin >> t;

    for (int i = 0; i < N; i++) {
        f[i][0] = 1;
        f[i][1] = i;
        f[i][2] = i * (i - 1ll) / 2;
    }

    while (t--) {
        cin >> n >> k;
        int x = n - 2, y = 2;
        ans = "";
        while (x > 0 || y > 0) {
            LL left = f[x + y - 1][y];
            if (k > left) {
                ans += 'b';
                y--;
                k -= left;
            } else {
                ans += 'a';
                x--;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
