/*
倒序分析：
- 69：前面有 2 个人
- 33：除去 69 之后，前面有 1 个人
- 51：除去 69、33 之后，前面有 1 个人

参考谜一样的牛即可
维护一个初始为全 1 的 01 序列，快速找到第 k 个 1 所在的位置，使用二分即可
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 2e5 + 10;

int n, a[N], c[N], h[N], ans[N];
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
    while (cin >> n) {
        memset(c, 0, sizeof c);
        for (int i = 1; i <= n; i++) {
            cin >> a[i] >> h[i];
            add(i, 1);
        }
        for (int i = n; i; i--) {
            int k = a[i] + 1;
            int l = 1, r = n;
            while (l < r) {
                int mid = l + r >> 1;
                if (ask(mid) >= k)
                    r = mid;
                else
                    l = mid + 1;
            }
            ans[l] = h[i];
            add(l, -1);
        }
        for (int i = 1; i <= n; i++) cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}