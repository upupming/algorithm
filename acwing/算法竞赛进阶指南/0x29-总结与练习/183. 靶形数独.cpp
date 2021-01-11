/*
跟 166 题数独完全一样
暴力搜索所有的解决方案，并计算分值即可，分值的计算可以用坐标到边界的最小距离+6即可
*/
#include <iostream>
using namespace std;
const int N = 9;

int row[N], col[N], cell[N][N], h[1 << N], cnt[1 << N], ans = -1;
int g[N][N];

inline void flip(int x, int y, int z) {
    row[x] ^= 1 << z;
    col[y] ^= 1 << z;
    cell[x / 3][y / 3] ^= 1 << z;
}
int getScore(int x, int y) {
    int dx = min(x, 8 - x), dy = min(y, 8 - y);
    return min(dx, dy) + 6;
}
// now: 剩余的没有填的位置数
// score: 到目前为止的得分总和
void dfs(int now, int score) {
    // 更新答案
    if (now == 0) {
        ans = max(ans, score);
        return;
    }
    // 找一个能填的合法数字最少的位置
    int minCh = 10, x, y;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (g[i][j] == 0) {
                auto choices = row[i] & col[j] & cell[i / 3][j / 3];
                int numCh = cnt[choices];
                if (numCh == 0) return;
                if (numCh < minCh) {
                    minCh = numCh;
                    x = i, y = j;
                }
            }
        }
    }

    // 枚举当前位置的所有的填充方法
    auto choices = row[x] & col[y] & cell[x / 3][y / 3];
    int s = getScore(x, y);
    for (int val = choices; val; val -= val & -val) {
        int num = h[val & -val];
        g[x][y] = num + 1;
        flip(x, y, num);
        dfs(now - 1, g[x][y] * s + score);
        flip(x, y, num);
        g[x][y] = 0;
    }
}
int main() {
    // log 计算
    for (int i = 0; i < N; i++)
        h[1 << i] = i;
    // 数中 1 的数量
    for (int i = 0; i < 1 << N; i++) {
        for (int j = i; j; j -= j & -j) {
            cnt[i]++;
        }
    }
    // 空白待填的个数
    int tot = 0, sum = 0;
    // 初始时，1~9 都可以填
    for (int i = 0; i < N; i++) {
        row[i] = col[i] = cell[i / 3][i % 3] = (1 << N) - 1;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> g[i][j];
            if (g[i][j] != 0) {
                sum += getScore(i, j) * g[i][j];
                flip(i, j, g[i][j] - 1);
            } else {
                tot++;
            }
        }
    }
    dfs(tot, sum);
    cout << ans << endl;
    return 0;
}