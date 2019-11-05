#include <iostream>

using namespace std;

long long q, a, b, c, s, n;
int main() {
    cin >> q;
    while (q--) {
        cin >> a >> b >> n >> s;
        // scanf("%d %d %d %d", &a, &b, &n, &s);
        bool ok;
        if (a * n < s) {
            ok = ((s - a * n) <= b);
        } else if (a * n == s) {
            ok = true;
        } else {
            ok = ((s % n) <= b);
        }
        printf("%s\n", ok ? "YES" : "NO");
    }
    return 0;
}