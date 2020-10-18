#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int t, n;
long long c[1010][1010];
long long sum[2020];
        // \: 0 1 2 3 4
        // 0: 0 0 0 0 0
        // 1: 1 1 1 1 0 -4
        // 2: 2 2 2 8 0 -3
        // 3: 1 1 1 0 0 -2
        // 4: 0 0 0 0 0 -1
// j - i:       4 3 2 1 0
// diagonal: -(n - 1) - (n - 1), 2n - 1
// [-4, 4] map to [0, 8]
// int solve() {

// }

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        fill(sum, sum + 2020, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> c[i][j];
                sum[j - i + (n - 1)] += c[i][j];
            }
        }

        printf("Case #%d: %lld\n", i, *max_element(sum, sum + 2020));
    }
    return 0;
}