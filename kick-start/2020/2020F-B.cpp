#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

int t, n, k, s[100010], e[100010], b[100010];

int solve() {
    // O(n log n)
    stable_sort(
        b, b + n,
        [](int left, int right) -> bool {
            // sort indices according to corresponding array element
            return s[left] < s[right];
        });
    int ans = 0, cur_ed = 0;
    for (int i = 0; i < n; i++) {
        int st = s[b[i]], ed = e[b[i]];
        if (cur_ed >= ed) continue;
        if (cur_ed > st) st = cur_ed;

        int add = ceil((double)(ed - st) / k);
        ans += add;
        cur_ed = st + add * k;
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> s[i] >> e[i];
            b[i] = i;
        }

        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}