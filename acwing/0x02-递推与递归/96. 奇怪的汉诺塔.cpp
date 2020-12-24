#include <climits>
#include <iostream>
using namespace std;

// 3 塔模式
int hanio_3(int n) {
    if (n == 1) return 1;
    return hanio_3(n - 1) * 2 + 1;
}

// 4 塔模式
int hanio_4(int n) {
    if (n == 1) return 1;
    int ans = INT_MAX;
    for (int i = 1; i < n; i++) {
        ans = min(ans, 2 * hanio_4(i) + hanio_3(n - i));
    }
    return ans;
}
int main() {
    for (int i = 1; i <= 12; i++) cout << hanio_4(i) << endl;
    return 0;
}