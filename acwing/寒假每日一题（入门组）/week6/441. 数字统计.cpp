/*
calc(x) 表示 1-x 里面的 2 的次数
calc(R) - calc(L - 1)
*/
#include <iostream>
using namespace std;

int l, r;
int calc(int x) {
    int ans = 0;
    for (int i = 1; i <= x; i++) {
        int y = i;
        while (y) {
            int r = y % 10;
            ans += r == 2;
            y /= 10;
        }
    }
    return ans;
}
int main() {
    cin >> l >> r;
    cout << calc(r) - calc(l - 1) << endl;
    return 0;
}