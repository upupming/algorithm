#include <iostream>>
using namespace std;
const int N = 110;

int t, dp[N][N], r, c, x;
int main() {
    cin >> t;
    while (t--) {
        cin >> r >> c;
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                cin >> x;
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]) + x;
            }
        }
        cout << dp[r][c] << endl;
    }
    return 0;
}