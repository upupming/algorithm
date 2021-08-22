#include <bits/stdc++.h>
using namespace std;

int t;
string s, u;

void solve() {
    cin >> s;
    int cnt[26] = {0}, sum = s.length();

    u = s;
    int n = s.length();
    vector<bool> used(n, false);
    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (sum - cnt[i] < cnt[i]) {
            puts("IMPOSSIBLE");
            return;
        }
    }

    for (int i = 0; i < n; i++) {
        if (u[i] == s[i]) {
            for (int j = 0; j < n; j++) {
                if (j == i) continue;
                if (u[j] != s[i] && u[i] != s[j]) {
                    swap(u[i], u[j]);
                    break;
                }
            }
        }
    }

    printf("%s\n", u.c_str());
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
