#include <cmath>
#include <iostream>
using namespace std;

long long t, n, a, b;
struct Pos {
    long long x, y;
    Pos(long long x, long long y) : x(x), y(y) {}
};
long long dis(const Pos& a, const Pos& b) {
    return round(10 * sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}
// m 从 0 开始索引
Pos getPos(long long n, long long m) {
    if (n == 0) return Pos(0, 0);
    long long len = 1ll << (n - 1), cnt = 1ll << (2 * n - 2);
    Pos pos = getPos(n - 1, m % cnt);
    // 根据情况进行翻转
    switch (m / cnt) {
        case 0:
            return Pos(pos.y, pos.x);
        case 1:
            return Pos(pos.x + len, pos.y);
        case 2:
            return Pos(pos.x + len, pos.y + len);
        case 3:
            return Pos(2 * len - (pos.y + len) - 1, 2 * len - pos.x - 1);
        default:
            return Pos(-1, -1);
    }
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> a >> b;
        cout << dis(getPos(n, a - 1), getPos(n, b - 1)) << endl;
    }
    return 0;
}