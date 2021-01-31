/*
迭代加深搜索需要的防御系统数量
*/
#include <iostream>
#include <vector>
using namespace std;
const int N = 60;

// up[i] 表示第 i 个单调上升子序列的结尾
// down[i] 表示第 i 个单调下降子序列的结尾
int n, a[N], e, up[N], down[N];
// 搜索到第 i 个导弹
// nu: 单调上升的序列个数
// nd: 单调下降的序列个数
bool dfs(int i, int nu, int nd) {
    // cout << "i: " << i << endl;
    // out();
    if (nu + nd > e) return false;
    if (i >= n) return true;
    // flag 表示能分给已存在的序列
    bool flag = false;
    // 尽量先分给已经存在的防御系统
    // 分给结尾最大的已经存在的上升序列（这一定是最优决策，贪心思想），注意 up 本身是单调递减的
    for (int j = 0; j < nu; j++) {
        if (up[j] < a[i]) {
            flag = true;
            int tmp = up[j];
            up[j] = a[i];
            if (dfs(i + 1, nu, nd)) return true;
            up[j] = tmp;
            break;
        }
    }
    // 如果不能放入任何已有序列，则需要新建
    if (!flag) {
        up[nu] = a[i];
        if (dfs(i + 1, nu + 1, nd)) return true;
    }

    flag = false;
    // 分给结尾最小的已经存在的下降序列（这一定是最优决策，贪心思想），注意 down 本身是单调递增的
    for (int j = 0; j < nd; j++) {
        if (down[j] > a[i]) {
            flag = true;
            int tmp = down[j];
            down[j] = a[i];
            if (dfs(i + 1, nu, nd)) return true;
            down[j] = tmp;
            break;
        }
    }
    // 如果不能放入任何已有序列，则需要新建
    if (!flag) {
        down[nd] = a[i];
        if (dfs(i + 1, nu, nd + 1)) return true;
    }

    return false;
}
int main() {
    while (cin >> n && n) {
        for (int i = 0; i < n; i++) cin >> a[i];
        e = 1;
        while (!dfs(0, 0, 0)) {
            e++;
        }
        cout << e << endl;
    }
    return 0;
}