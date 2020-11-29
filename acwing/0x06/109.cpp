/*
校验值的计算过程，每次都是选最大值和最小值进行组合
分成若干段的时候，要不超过 T，校验值要尽量小，肯定是大的数和小的数尽量分开，

固定左边界之后，倍增地枚举右边界即可

不用归并排序优化的话，cout/cin 会 TLF，scanf/printf 不会

下面是我经过归并排序优化之后的版本
*/
#include <algorithm>
#include <iostream>
using namespace std;

int k, n, m, a[500010], b[500010], c[500010];
long long t;
// 从 b 归并到 a
void merge(int l, int mid, int r) {
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r)
        if (b[i] <= b[j])
            c[k++] = b[i++];
        else
            c[k++] = b[j++];
    while (i <= mid)
        c[k++] = b[i++];
    while (j <= r)
        c[k++] = b[j++];
}
// l 到 mid 已经排好序了
long long calcT(int l, int mid, int r) {
    // for (int i = l; i <= r; i++) cout << " " << a[i];
    // cout << endl;
    // 这个函数会更新 b, c，即使这个组合不被接受
    // b 中的数据可能是脏的，需要重新复制一下
    for (int i = l; i <= r; i++) b[i] = a[i];
    // 剩下的部分自己排一下
    sort(b + mid + 1, b + r + 1);
    // 归并，减小了时间复杂度（相比全部直接排序）
    merge(l, mid, r);
    // for (int i = l; i <= r; i++) cout << " " << c[i];
    // cout << endl;
    long long ans = 0;
    for (int i = 0; i < m; i++) {
        int x = l + i, y = r - i;
        if (x < y) {
            long long diff = c[x] - c[y];
            ans += diff * diff;
        } else
            break;
    }
    // cout << l << ", " << r << ", " << ans << endl;
    return ans;
}
int main() {
    scanf("%d", &k);
    while (k--) {
        scanf("%d%d%lld", &n, &m, &t);
        for (int i = 0; i < n; i++) scanf("%d", &a[i]), c[i] = b[i] = a[i];
        int ans = 0;
        for (int l = 0; l < n; ans++) {
            // r 是尽量远离 l 的满足 <= t条件的下标
            int p = 1, r = l;
            while (p) {
                if (r + p < n && calcT(l, r, r + p) <= t) {
                    // 接受 c 中新增的排序部分
                    for (int i = l; i <= r + p; i++)
                        a[i] = c[i];
                    r += p, p *= 2;
                } else {
                    p /= 2;
                }
            }
            // cout << l << ", " << r << endl;
            l = r + 1;
        }
        printf("%d\n", ans);
    }

    return 0;
}
