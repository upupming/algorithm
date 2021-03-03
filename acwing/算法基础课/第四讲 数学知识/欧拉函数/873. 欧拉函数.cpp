/*
分解质因数之后算一下就得到答案了
*/
#include <iostream>
using namespace std;

int n, x;
int phi(int x) {
    int ans = x;
    for (int i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            ans = ans / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) ans = ans / x * (x - 1);
    return ans;
}
int main() {
    cin >> n;
    while (n--) {
        cin >> x;
        cout << phi(x) << endl;
    }
    return 0;
}
