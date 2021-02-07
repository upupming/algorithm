/*
乘法等价于幂次的加法，下面均以加法进行陈述

工作变量刚开始是 1 和 0，最终目标是能够最短时间内得到输入的整数 P
奶牛可以执行「加」操作和「减」操作，将结果存储在任意一个工作变量中

性质：
1. 0 是没有用的，因为 x - x 总是等于 0，任何时刻都可以得到 0，但是任何数加上和减去 0 都不变，不会产生新的数。
2. 负数是没有用的，减负数等价于加正数，加负数等价于减正数。

有了这两条性质，在选择减法操作时，总是用大数减去小数。如果有工作变量为 0，操作完之后，总是把 0 替换为新的结果。

另外的剪枝：
1. 在当前的深度下，如果剩下的步骤全部选择把较大的数扩大为2倍，还是小于目标状态，则剪枝（估价函数，IDA*）
2. 当前的值为 (a, b) 且 gcd(a, b) == d，不管怎么操作后续的结果都是 d 的倍数，如果不满足 d|P，则剪枝
*/
#include <algorithm>
#include <climits>
#include <iostream>
#include <unordered_set>
using namespace std;

int p, e;
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
bool dfs(int dep, int x, int y) {
    // 不妨设 x <= y
    if (x > y) swap(x, y);
    if (dep == e) {
        if (x == p || y == p) return true;
    }
    // 估价函数剪枝
    if (y << (e - dep) < p) return false;
    if (p % (gcd(x, y)) != 0) return false;

    unordered_set<int> c;
    // 执行「加」操作
    c.insert(x + y);
    c.insert(x + x);
    c.insert(y + y);
    // 执行「减」操作
    c.insert(y - x);
    for (auto &z : c) {
        if (z == 0 || z == x || z == y) continue;
        if (x == 0) {
            if (dfs(dep + 1, z, y)) return true;
        } else {
            if (dfs(dep + 1, z, x)) return true;
            if (dfs(dep + 1, z, y)) return true;
        }
    }
    return false;
}
int main() {
    cin >> p;
    while (!dfs(0, 1, 0)) e++;
    cout << e << endl;
    return 0;
}