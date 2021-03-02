/*
时间复杂度：O(sqrt(a) * n)
*/
#include <iostream>
using namespace std;

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int n, a;
int main() {
    cin >> n;
    while (n--) {
        cin >> a;
        cout << (is_prime(a) ? "Yes" : "No") << endl;
    }
    return 0;
}
