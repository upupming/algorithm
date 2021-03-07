/*
m[i] 不一定两两互质，中国剩余定理不再适用
使用数学归纳法
假设已经求出了前 k-1 个方程构成的方程组的一个解 x。
记 m = lcm(m1, m2, ..., m_{k-1})，则 x + im 是前 k-1 个方程的通解。（可以通过联立来证明通解的形式）

考虑第 k 个方程，求出一个整数 t，使得 x+tm = a_k (mod m_k)。
该方程等价于 m*t = a_k - x (mod m_k)，其中 t 是未知量。
这就是一个线性同余方程，可以用扩展欧几里得算法判断是否有解，并求出它的解
若有解，则 x' = x + tm 就是前 k 个方程构成的方程组的一个解

使用 n 次扩展欧几里得算法，就得到了整个方程组的解

具体的公式推导参见：https://www.acwing.com/solution/content/3539/
*/
#include <iostream>
using namespace std;
typedef long long LL;

LL extgcd(LL a, LL b, LL &x, LL &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    LL d = extgcd(b, a % b, x, y);
    int z = x;
    x = y;
    y = z - a / b * y;
    return d;
}
LL mod(LL a, LL b) {
    return (a % b + b) % b;
}

int n;
int main() {
    cin >> n;
    LL a1, m1;
    cin >> a1 >> m1;
    for (int i = 2; i <= n; i++) {
        LL a2, m2, k1, k2;
        cin >> a2 >> m2;
        LL d = extgcd(a1, -a2, k1, k2);
        if ((m2 - m1) % d == 0) {
            // 找到最小的解
            k1 = mod(k1 * (m2 - m1) / d, abs(a2 / d));
            m1 = k1 * a1 + m1;
            // lcm(a1, a2)
            a1 = abs(a1 / d * a2);
        } else {
            cout << -1 << endl;
            return 0;
        }
    }
    cout << m1 << endl;
    return 0;
}
