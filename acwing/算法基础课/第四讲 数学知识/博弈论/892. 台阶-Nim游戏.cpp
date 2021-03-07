/*
只需要考虑奇数级上的石子
把这些石子看成是一个经典的 Nim 游戏即可
*/
#include <iostream>
using namespace std;

int n, a;
int main() {
    cin >> n;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        if (i % 2)
            ans ^= a;
    }
    if (ans)
        puts("Yes");
    else
        puts("No");
    return 0;
}
