#include <algorithm>
#include <iostream>

using namespace std;

int t, k, a[10010], dpl[10010], dph[10010];

// 4 3 2 1: D C B A
/**
    4: A, B, C, D, dpl = a, dph = d
    3: BA, CB, DC
    2: CBA, DCB
    1: DCBA
    2: DCBAB

    dpl[i+1] = valid(dpl[i]-1 ~ dph[i]-1), if no valid, break the rule and restart
    the same for dph

4
5
1 5 100 500 1
8
2 3 4 5 6 7 8 9
9
4 3 2 1 5 4 3 2 1
4
1 2 3 4


1
9
1 2 3 4 1 2 3 4 5 6 7 8
//
0 1 2 3 4 5 6 7 8
 */
// 1 2 3 4: A B C D
// 1 5 100 500 1: A B C D C
// 2 3 4 5 6 7 8 9: A B C D A B C D

int solve() {
    int ans = 0;
    // 1 for A, 4 for D
    dpl[0] = 1, dph[0] = 4;
    for (int i = 1; i < k; i++) {
        if (a[i] == a[i - 1])
            dpl[i] = dpl[i - 1], dph[i] = dph[i - 1];
        else if (a[i] > a[i - 1]) {
            int l = dpl[i - 1] + 1;
            // have to break the law
            if (l > 4)
                dpl[i] = 1, dph[i] = 4, ans++;
            else
                dpl[i] = l, dph[i] = 4;
        } else {
            int h = dph[i - 1] - 1;
            // have to break the law
            if (h < 1)
                dpl[i] = 1, dph[i] = 4, ans++;
            else
                dpl[i] = 1, dph[i] = h;
        }
        // cout << i << ": " << dpl[i] << ", " << dph[i] << endl;
    }

    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> k;
        for (int i = 0; i < k; i++) {
            cin >> a[i];
        }

        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}