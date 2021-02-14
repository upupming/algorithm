#include <iostream>
using namespace std;

int n, ans;
int main() {
    cin >> n;
    bool flag = n < 0;
    n = abs(n);
    while (n) {
        int r = n % 10;
        ans = ans * 10 + r;
        n /= 10;
    }
    cout << (flag ? -ans : ans) << endl;
    return 0;
}