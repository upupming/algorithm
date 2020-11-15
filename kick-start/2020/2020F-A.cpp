#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

int t, n, a[100010], x, b[100010];

/*
2
3 3
2 7 4
5 2
9 9 9 9 8
*/

void solve() {
    stable_sort(b, b + n,
                [](int left, int right) -> bool {
                    // sort indices according to corresponding array element
                    return a[left] < a[right];
                });
    for (int i = 0; i < n; i++) {
        printf(" %d", b[i] + 1);
    }
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> x;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            // 10^15 必须要用 double，不然会 WA
            // https://www.cnblogs.com/bradmiller/archive/2010/11/25/1887945.html
            a[i] = ceil((double)a[i] / x);
            b[i] = i;
        }

        printf("Case #%d:", i);
        solve();
        printf("\n");
    }
    return 0;
}