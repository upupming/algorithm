/*
贪心 (邻项交换): 贪婪度大的孩子应该获得更多的饼干
    g[i] < g[j], 如果 i 获得的饼干更多 (c[i] > c[j])，可以将饼干数交换，其他的孩子不变，交换之后，i 增加了 g[i] 的怒气但是 j 减少了 g[j] 的怒气，总怒气减少。
把 N 个孩子按照贪婪度从大到小排序，他们分配到的饼干数将是单调不增的

f[i][j]:
状态表示:
    集合: 前 i 个孩子，一共分配 j 块饼干时，
    属性: 这 i 个孩子的怨气总和最小值。
状态计算:
    有两种情况:
    1. 第 i+1 个孩子获得的饼干数比第 i 个孩子少，a[i+1] = i
    2. 第 i+1 个孩子获得的饼干数与第 i 个孩子相同，此时还需要知道 i 前面有几个孩子与 i 获得的饼干数也相同，才能计算出 a[i+1]

    因此需要记录: 「第 i 个孩子获得的饼干数」、「i 前面有多少个孩子与 i 获得的饼干数相同」

    为了避免额外的记录这两个信息，分别做如下的处理:

    1. 若第 i 个孩子的饼干数大于 1，每人少拿一块饼干，饼干数相对顺序不变，因此 f[i][j] 和 f[i][j-1] 是等价的
    2. 若第 i 个孩子的饼干数等于 1，枚举一下前面有多少个孩子也获得 1 块饼干就可以了
初始条件 f[0][0] = 0
终止条件 f[n][m]
还需要求一下方案，只需要按照相对顺序分配好，之后剩下的全部给最大的那个人就可以了。
*/
#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 40, M = 5010;
typedef long long LL;

struct P {
    int g, idx, sum;
} p[N];
int n, m, ans[N];
LL f[N][M];
int main() {
    cin >> n >> m;
    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].g;
        p[i].idx = i;
    }
    // 按照贪婪值从大到小排序，保证后续分的饼干数从大到小
    sort(p + 1, p + 1 + n, [](auto& a, auto& b) {
        return a.g > b.g;
    });
    for (int i = 1; i <= n; i++) {
        p[i].sum = p[i - 1].sum + p[i].g;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= m; j++) {
            // 每人少拿一块饼干
            f[i][j] = f[i][j - i];
            // [k+1, i] 之间的孩子也获得 1 块饼干
            for (int k = 0; k < i; k++) {
                f[i][j] = min(
                    f[i][j],
                    f[k][j - (i - k)] + k * (p[i].sum - p[k].sum));
            }
        }
    }
    cout << f[n][m] << endl;

    int i = n, j = m, h = 0;
    while (i && j) {
        if (j >= i && f[i][j] == f[i][j - i])
            j -= i, h++;
        else {
            for (int k = 0; k < i; k++) {
                if (f[i][j] == f[k][j - (i - k)] + k * (p[i].sum - p[k].sum)) {
                    for (int u = i; u > k; u--) {
                        ans[p[u].idx] = 1 + h;
                    }
                    j = j - (i - k);
                    i = k;
                    break;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    return 0;
}
