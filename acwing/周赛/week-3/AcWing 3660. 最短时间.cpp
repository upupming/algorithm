#include <iostream>
using namespace std;

int t, n, m, r, c;
int main() {
    cin >> t;
    while (t--) {
        cin >> n >> m >> r >> c;
        int x = abs(r - 1) + abs(c - 1),
            y = abs(r - 1) + abs(c - m),
            z = abs(r - n) + abs(c - 1),
            w = abs(r - n) + abs(c - m);
        cout << max(max(x, y), max(z, w)) << endl;
    }
    return 0;
}
