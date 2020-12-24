#include <algorithm>
#include <iostream>
using namespace std;
const int N = 20;

// cab[i] 表示第 i 个缆车的承重，因为缆车至少可以放下一个小猫（W >= C_i），缆车数量 <= 小猫数量，数组开跟猫数量一样大就够了
int c[N], cab[N], n, w, ans = N;
// 处理第 now 只小猫的分配过程，目前已经用了 cnt 辆缆车
void dfs(int now, int cnt) {
    // 剪枝，不可能更优了
    if (cnt >= ans) return;
    if (now == n + 1) {
        ans = min(ans, cnt);
        return;
    }
    // 分配到已租用缆车
    for (int i = 1; i <= cnt; i++) {
        // 能装下
        if (cab[i] + c[now] <= w) {
            cab[i] += c[now];
            dfs(now + 1, cnt);
            cab[i] -= c[now];
        }
    }
    // 分配到新的缆车
    cab[cnt + 1] = c[now];
    dfs(now + 1, cnt + 1);
    cab[cnt + 1] = 0;
}
int main() {
    cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    // 重量较大的小猫显然比重量较轻的小猫更难运送，递减排序，优先送重猫，减少搜索树的分支数量
    // y 总讲的更容易理解的思路是：让最靠近根节点的分支尽量少，可以使搜索减小很多
    sort(c + 1, c + n + 1, greater<int>());
    dfs(1, 0);
    cout << ans << endl;
    return 0;
}