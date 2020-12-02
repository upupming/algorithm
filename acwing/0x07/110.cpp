/*
贪心：按照 minSPF 递减排序，每头牛选最大的能够满足条件的防晒霜使用

蓝书证明：防晒霜 x < y，选择 x 对后面的牛的影响，总没有选择 y 小
yxc 证明：不存在增广路经，是完美匹配
因为 SPF < 1000，可以直接用数组存
*/
#include <algorithm>
#include <iostream>
#include <numeric>
using namespace std;

int c, l, minSPF[2550], maxSPF[2550], cover[1010], idx[2550];
int main() {
    cin >> c >> l;
    for (int i = 0; i < c; i++) cin >> minSPF[i] >> maxSPF[i];
    int spf, cnt;
    // 这里注意可能有多种防晒霜有相同的 spf 值，所以用 +=
    for (int i = 0; i < l; i++) cin >> spf >> cnt, cover[spf] += cnt;

    // argsort 可以等价替换成 pair 的 sort
    // O(n log n)
    iota(idx, idx + c, 0);
    std::sort(idx, idx + c,
              [](int i, int j) -> bool {
                  // sort indices according to corresponding array element
                  return minSPF[i] > minSPF[j];
              });

    int ans = 0;
    // O(n)
    for (int i = 0; i < c; i++) {
        for (int j = maxSPF[idx[i]]; j >= minSPF[idx[i]]; j--) {
            if (cover[j]) {
                ans++, cover[j]--;
                // cout << idx[i] << ", " << j << endl;
                break;
            }
        }
    }

    cout << ans << endl;
    return 0;
}