#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int t, n, k, p, v[55][35];
// 缓存 dfs 结果
map<int, map<int, int>> m;

int dfs(int stack_no, int p) {
    if (m.count(stack_no) && m[stack_no].count(p)) {
        return m[stack_no][p];
    }

    if (p == 0) return 0;
    if (stack_no == n - 1) return v[stack_no][min(p - 1, k - 1)];

    int res = 0;
    // i 表示第 stack_no 叠盘子选择的盘子总数
    for (int i = 0; i <= min(p, k); i++) {
        // value 表示此次选择带来的收益价值
        int value = 0;
        if (i != 0) {
            value = v[stack_no][i - 1];
        }

        res = max(res, dfs(stack_no + 1, p - i) + value);
    }

    m[stack_no][p] = res;
    return res;
}

int solve() {
    // Prefix sum calculation
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < k; b++) {
            if (b != 0) {
                v[a][b] = v[a][b - 1] + v[a][b];
            }
        }
    }
    // DFS
    return dfs(0, p);
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        m.clear();
        cin >> n >> k >> p;
        for (int a = 0; a < n; a++) {
            for (int b = 0; b < k; b++) {
                cin >> v[a][b];
            }
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}