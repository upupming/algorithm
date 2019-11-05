#include <iostream>

using namespace std;

int n, d, m, a[1010], c[1010];
int main() {
    cin >> n >> m >> d;
    int sumC = 0;
    for (int i = 0; i < m; i++) {
        cin >> c[i];
        sumC += c[i];
    }
    if ((m + 1) * d + (sumC - m) < n + 1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        int dist = 0, j = 1;
        for (int i = 0; i < n; i++) {
            // cout << i << ", " << j << endl;
            dist++;
            // cout << (i + 1) << ", " << dist << endl;
            if (dist == d) {
                dist = 0;
                for (int k = 0; k < c[j - 1]; k++, i++) {
                    if (i != 0) cout << " ";
                    cout << j;
                }
                sumC -= c[j - 1];
                j++;
                i--;
            } else {
                // 虽然可以过，也必须放置这些垫子
                if (i + sumC >= n - 1 && j - 1 < m) {
                    // cout << endl << i << ", " << sumC << ", " << j << endl;
                    for (int k = 0; k < c[j - 1]; k++, i++, sumC--) {
                        if (i != 0) cout << " ";
                        cout << j;
                    }
                    j++;
                    i--;
                } else {                    
                    if (i != 0) cout << " ";
                    cout << 0;
                }
            }
        }
    }
    return 0;
}

/*
11 1 5
2

10 1 5
2
*/