#include <iostream>
#include <unordered_set>
using namespace std;
const int N = 100;

int t, x[N], n;
int main() {
    cin >> t;
    while (t--) {
        unordered_set<int> s;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> x[i];
            for (int j = 0; j < i; j++) {
                s.insert(abs(x[i] - x[j]));
            }
        }
        cout << s.size() << endl;
    }
    return 0;
}