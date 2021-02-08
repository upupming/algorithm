// 快速幂模板
#include <iostream>
using namespace std;

int a, b, p;
int kmi(int a, int b, int p) {
    int ans = 1 % p;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return ans;
}
int main() {
    cin >> a >> b >> p;
    cout << kmi(a, b, p) << endl;
    return 0;
}