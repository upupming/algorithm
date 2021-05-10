#include <iostream>
using namespace std;

int t, n, k;
string s;

void solve() {
    int dp = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] > s[i - 1])
            dp += 1;
        else
            dp = 1;
        cout << dp << " ";
    }
    cout << endl;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> s;
        s = ' ' + s;
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
