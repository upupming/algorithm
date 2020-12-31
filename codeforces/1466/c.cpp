#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 20;

int t, n, st[N];
string x;
int main() {
    cin >> t;
    while (t--) {
        int ans = 0;
        memset(st, 0, sizeof st);
        cin >> x;
        int n = x.length();
        for (int i = 0; i < n; i++) {
            if (st[i]) continue;
            if (i + 1 < n && x[i] == x[i + 1]) {
                st[i + 1] = 1;
                ans++;
            }
            if (i + 2 < n && x[i] == x[i + 2]) {
                st[i + 2] = 1;
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}