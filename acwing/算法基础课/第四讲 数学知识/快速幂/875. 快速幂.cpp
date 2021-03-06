#include <iostream>
using namespace std;

int n, a, b, p;
int qpow(int a, int b, int p) {
    int ans = 1 % p;
    while (b) {
        if (b & 1)
            ans = 1ll * ans * a % p;
        b >>= 1;
        a = 1ll * a * a % p;
    }
    return ans;
}
int main() {
    cin >> n;
    while (n--) {
        cin >> a >> b >> p;
        cout << qpow(a, b, p) << endl;
    }
    return 0;
}
