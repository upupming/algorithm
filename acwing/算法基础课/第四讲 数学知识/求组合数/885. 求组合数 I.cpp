/*
选第 1 个 c[a-1][b-1]，不选第 1 个 c[a-1][b]
c[a][b] = c[a-1][b-1] + c[a-1][b]
O(n^2)
*/
#include <iostream>
using namespace std;
const int N = 2100, P = 1e9 + 7;

int c[N][N];
int n, a, b;
int main() {
    // c[0][0] = 1 也是要初始化的，不然就错了
    for (int i = 0; i < N; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
            c[i][j] %= P;
        }
    }

    cin >> n;
    while (n--) {
        cin >> a >> b;
        cout << c[a][b] << endl;
    }
    return 0;
}
