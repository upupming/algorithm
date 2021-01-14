/*
实数二分
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;

int n, m, a[N];
bool valid(double len) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += int(a[i] / len);
    }
    return cnt >= m;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    double l = 0, r = 1e9;
    while (abs(l - r) > 1e-4) {
        double mid = (l + r) / 2;
        if (valid(mid))
            l = mid;
        else
            r = mid;
    }
    printf("%.2lf\n", l);
}