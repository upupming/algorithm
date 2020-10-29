/**
Simple, reorder doesn't change the result, which is the sum of the total array
 */

#include <iostream>

using namespace std;

int t, n, m;

int main() {
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n >> m;
        int sum = 0, tmp;
        for (int i = 0; i < n; i++) {
            cin >> tmp;
            sum += tmp;
        }
        cout << ((sum == m) ? "YES" : "NO") << endl;
    }
    return 0;
}