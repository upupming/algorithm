/*
暴力枚举所有的 A' 计算最接近的 B'，然后比较是否更接近原来的答案即可
*/
#include <iostream>
using namespace std;

int a, b, ap = 1, bp = 1, l;
int gcd(int a, int b) { b > 0 ? gcd(b, a % b) : a; }
int main() {
    cin >> a >> b >> l;
    // bool flag = a < b;
    // if (flag) swap(a, b);
    double d = 1e10;
    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= l; j++) {
            if (gcd(i, j) != 1) continue;
            double diff = 1.0 * i / j - 1.0 * a / b;
            if (diff >= 0 && diff < d) {
                d = diff;
                ap = i;
                bp = j;
            }
        }
    }
    // if (flag) swap(ap, bp);
    cout << ap << " " << bp << endl;
    return 0;
}
