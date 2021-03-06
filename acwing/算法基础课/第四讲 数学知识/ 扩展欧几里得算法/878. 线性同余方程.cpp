#include <iostream>
using namespace std;

int extgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = extgcd(b, a % b, x, y);
    int z = x;
    x = y;
    y = z - a / b * y;
    return d;
}

int n, a, b, m, x, y;
int main() {
    cin >> n;
    while (n--) {
        cin >> a >> b >> m;
        int d = extgcd(a, m, x, y);
        if (b % d == 0)
            // 输出答案必须在int范围之内。所以取一下模
            // 蓝书上证明答案与特解 x* 模 m/d 同余即可，其实模 m 也行，因为 m 已经在 int 范围内了
            cout << 1ll * x * b / d % (m / d) << endl;
        else
            cout << "impossible" << endl;
    }
    return 0;
}
