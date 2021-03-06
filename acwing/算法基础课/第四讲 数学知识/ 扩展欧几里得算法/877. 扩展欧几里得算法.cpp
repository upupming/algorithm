#include <iostream>
using namespace std;

int extgcd(int a, int b, int& x, int& y) {
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

int n, a, b, x, y;
int main() {
    cin >> n;
    while (n--) {
        cin >> a >> b;
        extgcd(a, b, x, y);
        cout << x << " " << y << endl;
    }
    return 0;
}
