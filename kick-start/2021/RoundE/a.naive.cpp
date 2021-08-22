#include <bits/stdc++.h>
using namespace std;

int t;
string s, u;

void solve() {
    cin >> s;
    u = s;
    int n = s.length();
    do {
        next_permutation(u.begin(), u.end());
        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (u[i] == s[i]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            puts(u.c_str());
            return;
        }
    } while (u != s);
    puts("IMPOSSIBLE");
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
