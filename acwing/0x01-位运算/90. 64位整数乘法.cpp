#include <iostream>

using namespace std;

// 按位排列：b = c_{k - 1} ... c_{0}
// b = \sigma_{i = k - 1 ... 0} c_{i} * 2^{i}
// a * b = \sigma_{i = k - 1 ... 0}  a * c_{i} * 2^{i}
// a * {2^{i}} 存在临时变量里面（还用 a 保存），每次 i + 1 等价于进行 * 2 操作

int main() {
    long long a, b, p;
    cin >> a >> b >> p;
    long long ans = 0;
    for (; b > 0; b >>= 1) {
        if (b & 1) ans = (ans + a) % p;
        a = a * 2 % p;
    }
    cout << ans << endl;

    return 0;
}