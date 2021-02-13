/*
最后一头牛前面有 A_n 头牛比他低，他的身高就是 A_n + 1
倒数第二头牛前面有 A_{n-1} 头牛比他低，他的身高：
1. 如果 A_{n-1} < A_n，他的身高就是 A_{n-1} + 1
2. 否则，他的身高就是 A_{n-1} + 2
第 k 头牛前面有 A_k 头比它低，那么他的身高 H_k 是 1~n 里面的第 A_k + 1 小的，但是没有出现在 {H_{k+1}, ..., H_{n}} 中出现过的数

长度为 n 的 01 序列 b，起始全部为 1。
从 n 到 1 扫描每个 A_i，执行操作：
1. 查询 b 中第 A_i + 1 个 1 在什么位置，这个位置就是这头牛的身高H_i
2. b[H_i] 设为 0（这个数已经被后面的牛给用掉了），也就是将 b[H_i] 减 1

因此，我们就是要查询第 k 个 1 在什么位置

树状数组+二分：
树状数组 c 维护 01 序列 b 的前缀和，每次查询时，二分答案，ask(mid) 可以得到前 mid 个数中有多少个 1，与 k 比较大小，进行上下界的变化即可
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;

int n, a[N], c[N], h[N];
// 查询前缀和：查询序列 a 第 1~x 个数的和
int ask(int x) {
    int ans = 0;
    for (; x; x -= x & -x) ans += c[x];
    return ans;
}
// 单点增加：给序列中的一个数 a[x] 加上 y
// 算法：自下而上每个节点都要增加 y
void add(int x, int y) {
    for (; x <= n; x += x & -x) c[x] += y;
}
int main() {
    cin >> n;
    a[1] = 0, add(1, 1);
    for (int i = 2; i <= n; i++) {
        cin >> a[i];
        add(i, 1);
    }
    for (int i = n; i; i--) {
        int k = a[i] + 1;
        // cout << k << endl;
        int l = 1, r = n;
        while (l < r) {
            int mid = l + r >> 1;
            if (ask(mid) >= k)
                r = mid;
            else
                l = mid + 1;
        }
        // cout << i << " " << l << " " << ask(l) << endl;
        h[i] = l;
        add(l, -1);
    }
    for (int i = 1; i <= n; i++) cout << h[i] << endl;
    return 0;
}