/*
样例的 3 等差数列：
13: 0-13-26-39-52
12: 3-15-27-39-51
8:  5-13-21-29-37-45-53
目标：找到 3 个起始点，3 个公差

算法：先预处理出所有合法路线
首项：a
公差：d
那么一定有 a - d < 0，也就是 d >= a + 1
等差数列至少有两个数，所有要求 a + d < 60

最少选择多少条（k）路线，可以将所有公交车（n）覆盖
组合问题
剪枝：
1. dfs 时需要传入一个枚举的起点
2. 优先枚举点较多的路线
3. 如果当前路线上的点数 * 剩余可以选择的路线数量 + 现在已经覆盖的公交车数量 < 总公交车数，直接回溯
*/
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;
// 从 60 个时间点中选择两个点就可以确定一个等差数列，所以总的方案数不超过 C_60^2 < 2000
const int N = 2000, M = 60;
typedef pair<int, int> PII;
typedef pair<int, PII> PIII;
vector<PIII> routes;

int n, t, bus[M], e;

bool check(int a, int d) {
    for (int i = a; i < 60; i += d) {
        // 如果某个时刻没有公交车
        if (!bus[i]) return false;
    }
    return true;
}

// dep: 已经选择的路线数量
// sum: 当前所有线路已经容纳的公交车数量
// start: 当前可以选的路线的开始下标
bool dfs(int dep, int sum, int start) {
    if (dep == e) return sum == n;

    // 枚举选哪个路线
    for (int i = start; i < routes.size(); i++) {
        auto r = routes[i];
        int a = r.second.first, d = r.second.second;
        // 后续不管怎么选，都不可能超出 n，剪枝 3
        if (r.first * (e - dep) + sum < n) continue;
        if (!check(a, d)) continue;
        for (int j = a; j < 60; j += d) bus[j]--;
        if (dfs(dep + 1, sum + r.first, i)) return true;
        // 还原现场
        for (int j = a; j < 60; j += d) bus[j]++;
    }

    return false;
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> t;
        bus[t]++;
    }
    // 枚举所有的首项
    for (int a = 0; a < 60; a++) {
        // 枚举所有公差
        for (int d = a + 1; a + d < 60; d++) {
            if (check(a, d)) {
                routes.push_back({// 路线上的公交车数量
                                  (59 - a) / d + 1,
                                  {a, d}});
            }
        }
    }
    // 按照「路线上的公交车数量」对所有路线从大到小排序，用于优先选择数量多的路线（剪枝2）
    sort(routes.begin(), routes.end(), greater<PIII>());

    e = 1;
    while (!dfs(0, 0, 0)) e++;
    cout << e << endl;
    return 0;
}