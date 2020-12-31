/*
依次搜索每个位置 k，枚举 i 和 j 作为分支，把 X[i] 和 X[j] 的和填到 X[k] 上，然后递归填写下一个位置
剪枝：
1. 优化搜索顺序：i, j 从大到小枚举
2. 排除等效冗余：不同的 i, j 组合，X[i]+X[j] 可能相等，用 bool 进行判重，避免重复搜索（实测只能使用 bool 数组，使用 unordered_set 会超时）

m 的值（序列长度） <= 10，可以使用迭代加深搜索

dfs(k) 表示搜索到位置 k 了
*/
#include <cstring>
#include <iostream>
using namespace std;

int n, d, a[20];
bool seen[110];
bool dfs(int k) {
    if (k == d) return a[k] == n;
    memset(seen, 0, sizeof(seen));
    // 接下来填第 k + 1 个数
    for (int i = k; i >= 1; i--) {
        for (int j = i; j >= 1; j--) {
            int sum = a[i] + a[j];
            // 必须加上 sum >= a[k]，否则会 WA，不满足递减规定了
            if (sum >= a[k] && sum <= n && !seen[sum]) {
                a[k + 1] = sum;
                seen[sum] = true;
                if (dfs(k + 1)) return true;
            }
        }
    }
    return false;
}
int main() {
    a[1] = 1;
    while (cin >> n && n) {
        for (d = 1;; d++) {
            if (dfs(1)) {
                for (int i = 1; i <= d; i++) {
                    cout << a[i] << " ";
                }
                cout << endl;
                break;
            }
        }
    }
    return 0;
}