#include <cmath>
#include <iostream>
using namespace std;

/*
看到这一题，感觉有种似曾相识的感觉
能否用线段树进行求解？不是很懂

index: 1 2 3 4 5
    a: 1 1 2 2
    b: 1 0 1 0 0
   b1: 2 0 0 0 0 (b[3]--，选 b[1] 和 b[j])
   b2: 1 0 0 0 0 (b[3]--，选 b[i] 和 b[n+1])

index: 1 2 3 4  5 6 7
    a: 1 1 2 2  1 1
    b: 1 0 1 0 -1 0 0
   b1: 2 0 0 0  0 0 0 (b[3]--, b[5]++)

b[2], ..., b[n] 正数绝对值之和 p，负数绝对值之和为 q；
一共需要 min(p, q) 次互相组合，加上 |p-q| 次中间的 b 和开始或结尾组合
最少操作次数为 min(p, q) + |p-q| = max(p, q)
总的方案数为：
    1. 中间元素互相组合方式不同，最终结果都是一样的
    2. |p-q| 次与首或者尾组合，与 b[1] 可以组合 0 次、1 次、...、|p-q| 次，得到的 b[1] 值都不同的，而 b[1] 就是代表最终的整个数组的值，所以共有 |p-q|+1 次方案
*/
typedef long long LL;
int n, a[100010], b[100010];
// p, q 要求和，所以用 LL
LL p, q;
int main() {
    cin >> n;
    for (int i = 1, x; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i] - a[i - 1];
        if (i >= 2) {
            if (b[i] > 0) {
                p += b[i];
            } else {
                q += -b[i];
            }
        }
    }
    cout << max(p, q) << endl
         << (abs(p - q) + 1) << endl;
    return 0;
}