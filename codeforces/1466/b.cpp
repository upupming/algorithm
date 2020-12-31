#include <iostream>
#include <unordered_set>
using namespace std;
const int N = 1e5 + 20;

int t, n, x[N];
int main() {
    cin >> t;
    while (t--) {
        unordered_set<int> s;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> x[i];
        }
        for (int i = n - 1; i >= 0; i--) {
            if (!s.count(x[i] + 1))
                s.insert(x[i] + 1);
            else
                s.insert(x[i]);
        }
        cout << s.size() << endl;
    }
    return 0;
}