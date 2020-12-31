#include <cstring>
#include <iostream>
using namespace std;
const int N = 5e5 + 10;
const int P = 60;
const int MOD = 1e9 + 7;
typedef long long LL;

/*
这题卡 cin，N = 5 * 10^5
*/

LL a[N];
// cnt[j] 表示第 j 为上有多少 1
int t, n, cnt[P];
int main() {
    cin.sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--) {
        memset(cnt, 0, sizeof cnt);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            for (int j = 0; j < P; j++) {
                cnt[j] += a[i] >> j & 1;
            }
        }

        int ans = 0;
        // 最外层遍历所有数
        for (int i = 0; i < n; i++) {
            // 两项之积
            LL expOr = 0, expAnd = 0;
            for (int j = 0; j < P; j++) {
                if (a[i] >> j & 1) {
                    expAnd += (1LL << j) % MOD * cnt[j];
                    expOr += (1LL << j) % MOD * n;
                } else
                    expOr += (1LL << j) % MOD * cnt[j];
            }

            expAnd %= MOD, expOr %= MOD;
            ans = (ans + expAnd * expOr) % MOD;
        }
        cout << ans << endl;
    }
    return 0;
}