/*
DFS 框架：在每个状态下找出一个「最小」的正方形，枚举去掉它边界上的哪一根火柴，然后沿着该分支深入
估价函数设计：不断从当前图形中任选一个还没有被破坏的正方形，去掉它边界上的所有火柴棒，但是只记作一次操作。按照上述方法统计出破坏所有正方形需要多少此操作，作为估计值 f，f <= 未来实际需要去掉的火柴数
IDA*: 枚举最多去掉次数（层数）

选做题，火柴棒编号、图形样式处理较为繁琐，直接看答案了。

重复覆盖问题
行：每个火柴，列：每个正方形
0/1 矩阵，1 表示火柴在正方形上面（让我回想到了 bitset 的做法，sudoku，dancing links）
每一行表示火柴在哪些正方形上，每一列表示每个正方形由哪些火柴构成
至少选择多少行，可以使得每一列至少有一个 1
*/
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
// 对于边长为 5 的网格来说，一共有 5 * 6 * 2 = 60 条边
const int N = 100;

// e 表示最大深度
int t, n, k, cnt, e, st[N], cpy[N];
vector<int> squares[N];

int f() {
    memcpy(cpy, st, sizeof(st));
    int ans = 0;
    for (int i = 0; i < cnt; i++) {
        bool broken = false;
        // 看第 i 个正方形是否已经被破坏
        for (int j = 0; j < squares[i].size(); j++) {
            if (st[squares[i][j]]) {
                broken = true;
                break;
            }
        }
        if (!broken) {
            ans++;
            for (int j = 0; j < squares[i].size(); j++) {
                st[squares[i][j]] = 1;
            }
        }
    }

    memcpy(st, cpy, sizeof(st));
    return ans;
}
// 能否破坏所有正方形
bool dfs(int dep) {
    int cost = f();
    if (cost == 0) return true;
    if (dep + cost > e) return false;

    // 找出最小的正方形，枚举去掉它边界上的哪一根火柴，然后沿着该分支深入
    for (int i = 0; i < cnt; i++) {
        bool broken = false;
        // 看第 i 个正方形是否已经被破坏
        for (int j = 0; j < squares[i].size(); j++) {
            if (st[squares[i][j]]) {
                broken = true;
                break;
            }
        }
        if (broken) continue;
        // 找到第一个最小的完整的正方形，枚举每一条边
        for (int j = 0; j < squares[i].size(); j++) {
            st[squares[i][j]] = 1;
            if (dfs(dep + 1)) return true;
            st[squares[i][j]] = 0;
        }
        // 枚举完所有的边仍然不行，无解
        return false;
    }
    // 所有正方形都已经被破坏，已经找到一个解
    return true;
}
int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        cnt = 0;
        // 枚举所有不同边长的正方形
        for (int len = 1; len <= n; len++) {
            // 枚举行坐标
            for (int i = 1; i + len - 1 <= n; i++) {
                // 枚举列坐标
                for (int j = 1; j + len - 1 <= n; j++) {
                    // 找一下每个正方形构成的边的编号规律即可
                    squares[cnt].clear();
                    // 对于长为 len 的边长的每一根火柴
                    for (int k = 0; k < len; k++) {
                        // 上下公差
                        int d = 2 * n + 1;
                        // 上边的火柴
                        squares[cnt].push_back(d * (i - 1) + j + k);
                        // 下边的火柴
                        squares[cnt].push_back(d * (i + len - 1) + j + k);
                        // 左边的火柴
                        squares[cnt].push_back(n + d * (i + k - 1) + j);
                        // 右边的火柴
                        squares[cnt].push_back(n + d * (i + k - 1) + j + len);
                    }
                    cnt++;
                }
            }
        }
        // for (int i = 0; i < cnt; i++) {
        //     for (int j = 0; j < squares[i].size(); j++) {
        //         cout << squares[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        // 计算 st 数组
        memset(st, 0, sizeof st);
        cin >> k;
        for (int i = 0, t; i < k; i++) {
            cin >> t;
            // 1 表示边被删除
            st[t] = 1;
        }

        // 迭代加深
        e = 0;
        while (!dfs(0)) e++;
        cout << e << endl;
    }
    return 0;
}