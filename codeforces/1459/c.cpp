#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll n, m, a[N], b[N];
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll cd = 0;
    sort(a, a + n);
    for (int i = 1; i < n; i++)
        cd = gcd(cd, a[i] - a[i - 1]);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        cout << gcd(cd, a[0] + b[i]) << " ";
    }
    cout << endl;
    return 0;
}