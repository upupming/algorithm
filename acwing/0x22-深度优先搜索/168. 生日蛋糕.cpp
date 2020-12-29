/*
按题目要求，面积、体积在表示的时候都可以省去 \Pi
上表面面积等于最底层的圆面积，可以在第 M 层直接累加
用全局变量 h 和 r 记录每层的高度和半径
dfs(dep, s, v)
    - dep: 正在搜索第 dep(th) 层
    - s: 当前外表面面积
    - v: 当前体积
    - h[dep+1], r[dep+1]: 第 depth+1 层的高度和半径

剪枝：
1. 上下界剪枝
在 dep 层时，只在下面的范围枚举：
- R: [dep, min(sqrt(N-v), r[dep+1]-1)]
- H: [dep, min((N-v)/R^2, h[dep+1]-1)]
2. 优化搜索顺序
R 和 H 在上述范围中，使用倒序枚举（面积、体积增大的比较快，方案越少）
3. 可行性剪枝
预处理前 i 层的最小体积和侧面积。就是第 1~i 层的半径分别取 1,2,3,...,i，高度分别取 1,2,3,...,i 时，有最小的体积与侧面积。
如果当前体积 v 加上 1~dep-1 层的最小体积大于 N，可以剪枝
4. 最优性剪枝一
如果当前表面积 s 加上 1~dep-1 层的最小侧面积大于已经搜到的答案，可以剪枝
5. 最优性剪枝二
当 2(n-v)/r[dep]+s 大于已经搜到的答案时，可以剪枝

思考时间：35 分钟
写代码+调试时间：27 分钟
*/
#include <cmath>
#include <iostream>
using namespace std;
const int M = 30, inf = 1e9;

int h[M], r[M], n, m, ans = inf, minS[M], minV[M];
void dfs(int dep, int s, int v) {
    // 所有层搜索完成，更新答案
    if (dep == 0) {
        if (n == v)
            ans = min(ans, s);
        return;
    }
    // 剪枝 3, 4
    if (v + minV[dep - 1] > n || s + minS[dep - 1] > ans) return;
    // 剪枝 1
    int rMax = min((int)sqrt(n - v), r[dep + 1] - 1);
    // 剪枝 2
    for (int curR = rMax; curR >= dep; curR--) {
        // 剪枝 5
        if (2 * (n - v) / curR + s > ans) return;

        int hMax = min((n - v) / curR / curR, h[dep + 1] - 1);
        // 剪枝 2
        for (int curH = hMax; curH >= dep; curH--) {
            r[dep] = curR;
            h[dep] = curH;
            dfs(dep - 1,
                s + 2 * curR * curH +
                    (dep == m ? curR * curR : 0),
                v + curR * curR * curH);
        }
    }
}
int main() {
    cin >> n >> m;
    // 预处理计算 1~m 层的最小侧面积和体积
    for (int i = 1; i <= m; i++) {
        minS[i] = minS[i - 1] + 2 * i * i;
        minV[i] = minV[i - 1] + i * i * i;
    }
    // 加个哨兵方便 dfs 剪枝
    r[m + 1] = h[m + 1] = inf;

    dfs(m, 0, 0);
    cout << (ans == inf ? 0 : ans) << endl;
    return 0;
}
