#include <algorithm>
#include <iostream>

using namespace std;

int k, n, a[1010];
int main() {
    cin >> k;
    while (k--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a, a + n);
        int i, j;
        for (i = 0; i < n; i++) {
            j = n - 1 - i;
            if (i + 1 > a[j]) break;
        }

        // cout << "ans: ";
        cout << i << endl;
    }
}