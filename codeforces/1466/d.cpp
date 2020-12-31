#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 20;
typedef long long LL;

int t, n, deg[N], w[N], u, v;
int main() {
    cin >> t;
    while (t--) {
        LL ans = 0;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            deg[i] = 0;
            cin >> w[i];
            ans += w[i];
        }
        vector<int> a;
        for (int i = 1; i <= n - 1; i++) {
            cin >> u >> v;
            deg[u]++, deg[v]++;
            if (deg[u] > 1) a.push_back(w[u]);
            if (deg[v] > 1) a.push_back(w[v]);
        }
        sort(a.begin(), a.end(), greater<int>());
        assert(a.size() == n - 2);
        cout << ans;
        for (int i = 0; i < n - 2; i++) {
            cout << " " << (ans += a[i]);
        }
        cout << endl;
    }
    return 0;
}