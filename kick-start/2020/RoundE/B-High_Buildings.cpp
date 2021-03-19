/*
只需要构造一种合法的方案即可

x = N - (A+B-C) 表示两个人都看不见的数量，x < 0 的话，一定不能够满足

先把 C 个最高的放在正中央，放高度为其他的总不会优于放 N，因此就都定为高度 N
接下来：
- 把 A-C 个 N-1 放在左边
- 把 B-C 个 N-1 放在右边
这样总共放了 A+B-C 个看得见的了，接下来是 x 个看不见的
这样，看不见的直接插入到左边到正中央之间，高度为 N-2 即可；也可以直接插入到正中间到右边之间，高度为 N-2
需要特判的情况是：
- N-1 <= 0，也就是 N=1，这种情况只能放N=1，因此必须要求 A=B=C=N
- N-2 <= 0，也就是 N=2，左右两边最低只能放 N-1 = 1，那么就必须要求 x = 0；而且只能是 [1, 2]、[2, 2] 和 [2, 1] 这三种情况
*/
#include <cassert>
#include <iostream>
using namespace std;

int t, n, a, b, c;

bool solve() {
    int left, mid, right;
    int x = n - (a + b - c);
    if (x < 0) return false;

    if (n == 1) {
        if (a == 1 && b == 1 && c == 1) {
            cout << 1 << endl;
        } else
            return false;
    } else if (n == 2) {
        if (a == 2 && b == 1 && c == 1) {
            cout << 1 << " " << 2 << endl;
        } else if (a == 2 && b == 2 && c == 2) {
            cout << 2 << " " << 2 << endl;
        } else if (a == 1 && b == 2 && c == 1) {
            cout << 2 << " " << 1 << endl;
        } else {
            return false;
        }
    } else {
        mid = c, left = a - c, right = b - c;
        assert(left + mid + right + x == n);
        // 需要隐蔽，但是无缝可插
        if (left + mid + right <= 1 && x != 0) return false;
        // 插入到中央和右边之间
        int flag = 0;
        // 插入到中央和左边之间
        if (left > 0) flag = 1;
        // 插入到中央的第一根和第二根之间
        if (mid > 1) flag = 2;

        while (left--) cout << n - 1 << " ";
        if (flag == 1)
            while (x--) cout << n - 2 << " ";
        if (flag == 2) {
            cout << n << " ";
            mid--;
            while (x--) cout << n - 2 << " ";
        }
        while (mid--) cout << n << " ";
        if (flag == 0)
            while (x--) cout << n - 2 << " ";
        while (right--) cout << n - 1 << " ";
        cout << endl;
    }
    return true;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> a >> b >> c;
        printf("Case #%d: ", i);
        if (!solve()) {
            puts("IMPOSSIBLE");
        }
    }
    return 0;
}
