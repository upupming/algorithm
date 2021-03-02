/*
每一个 a，分解的时间复杂度为 sqrt(a)，总时间复杂度为 O(n sqrt(a))
*/
#include <iostream>
using namespace std;

int n, a;

void divide(int x) {
    for (int i = 2; i <= x / i; i++) {
        // 如果 x % i == 0，i 一定是质数，否则已经被分解过了
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) x /= i, s++;
            cout << i << " " << s << endl;
        }
    }
    // 最后剩下一个大于 sqrt(x) 的约数
    if (x > 1) cout << x << " " << 1 << endl;
    cout << endl;
}

int main() {
    cin >> n;
    while (n--) {
        cin >> a;
        divide(a);
    }
    return 0;
}
