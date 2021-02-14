/*
O(sqrt(N)) 时间复杂度
*/
#include <cmath>
#include <iostream>
using namespace std;
const int N = 1e5 + 10;

int n, v[N];
int main() {
    cin >> n;
    int m = sqrt(n);
    for (int i = 2; i <= m; i++) {
        // 只考虑素数，其实因为题目保证是素数，可以不加这个素数筛也可以过
        if (v[i]) continue;
        for (int j = i; j <= m / i; j++) v[i * j] = 1;
        if (n % i == 0) {
            cout << n / i << endl;
            return 0;
        }
    }
    return 0;
}