#include <iostream>
using namespace std;
const int N = 110;

int n, m, a[N][N];
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[n - 1 - j][i] << " ";
        }
        cout << endl;
    }
    return 0;
}
