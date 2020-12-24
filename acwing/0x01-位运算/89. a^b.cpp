#include <iostream>

using namespace std;

// 按位排列：b = c_{k - 1} ... c_{0}
// b = \sigma_{i = k - 1 ... 0} c_{i} * 2^{i}
// a^b = \Pi_{i = k - 1 ... 0} a^{c_{i} * 2^{i}}
// a^{2^{i}} 存在临时变量里面（还用 a 保存），每次 i + 1 等价于进行平方操作

int main() {
    int a, b, p;
    cin >> a >> b >> p;
    // 这里也要 % p，因为可能不进入循环
    int ans = 1 % p;
    for (; b > 0; b >>= 1) {
        if (b & 1) ans = (long long)ans * a % p;
        a = (long long)a * a % p;
    }
    cout << ans << endl;

    return 0;
}