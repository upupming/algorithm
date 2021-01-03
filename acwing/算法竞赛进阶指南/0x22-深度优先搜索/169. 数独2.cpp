/*
太难了，直接看答案
看视频+实现时间：1 小时 24 分钟
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 16, M = N * N + 1;

// log[2^i] = i，ones[i] = i 有多少个 1
int ones[1 << N], log[1 << N];
// 每个空格的所有备选数字
int state[N][N];
// 用于恢复现场的备份
int bstate[M][N][N], bstate2[M][N][N];
// 数独数组
char str[N][N + 1];
// 数独数组备份
char bstr[M][N][N + 1];
void draw(int x, int y, int c) {
    str[x][y] = c + 'A';
    // 行、列
    for (int i = 0; i < N; i++) {
        state[x][i] &= ~(1 << c);
        state[i][y] &= ~(1 << c);
    }
    int sx = x / 4 * 4, sy = y / 4 * 4;
    for (int i = sx; i < sx + 4; i++) {
        for (int j = sy; j < sy + 4; j++) {
            state[i][j] &= ~(1 << c);
        }
    }
    state[x][y] = 1 << c;
}
bool dfs(int cnt) {
    if (cnt == 0) return true;

    // 备份当前状态
    int kcnt = cnt;
    memcpy(bstate[kcnt], state, sizeof state);
    memcpy(bstr[kcnt], str, sizeof str);

    // 对于每个空格剪枝：如果一个都不能填，无解；只能填一个，直接填
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (str[i][j] == '-') {
                int s = state[i][j];
                if (!s) {
                    memcpy(state, bstate[kcnt], sizeof state);
                    memcpy(str, bstr[kcnt], sizeof str);
                    return false;
                }

                if (ones[s] == 1) {
                    draw(i, j, log[s]);
                    cnt--;
                }
            }
        }
    }
    // 对于每一行，如果某个字母不能出现在任何一个位置，则无解
    // 如果某个字母，只能在一个位置上，则直接填
    for (int i = 0; i < N; i++) {
        // sor 表示整个行所有候选字母
        // sand 表示只能在某个位置的那些数
        int sor = 0, sand = (1 << N) - 1;
        // 这一行上已经填过的字母
        int drawn = 0;
        for (int j = 0; j < N; j++) {
            int s = state[i][j];
            // 如果既能在前面备选，又能在当前备选，就从 sand 去掉
            sand &= ~(s & sor);
            sor |= s;

            if (str[i][j] != '-') drawn |= state[i][j];
        }
        // 如果某个字母不能出现在任何一个位置，则无解
        if (sor != (1 << N) - 1) {
            memcpy(state, bstate[kcnt], sizeof state);
            memcpy(str, bstr[kcnt], sizeof str);
            return false;
        }
        // 如果某个字母，只能在一个位置上，则直接填
        for (int j = sand; j; j -= j & -j) {
            int t = j & -j;
            if (!(drawn & t)) {
                // 找到对应的位置 k，t 代表的字母只能在 k 处出现
                for (int k = 0; k < N; k++) {
                    if (state[i][k] & t) {
                        draw(i, k, log[t]);
                        cnt--;
                    }
                }
            }
        }
    }

    // 对于每一列，如果某个字母不能出现在任何一个位置，则无解
    // 如果某个字母，只能在一个位置上，则直接填
    for (int i = 0; i < N; i++) {
        // sor 表示整个列所有候选字母
        // sand 表示只能在某个位置的那些数
        int sor = 0, sand = (1 << N) - 1;
        // 这一列上已经填过的字母
        int drawn = 0;
        for (int j = 0; j < N; j++) {
            int s = state[j][i];
            // 如果既能在前面备选，又能在当前备选，就从 sand 去掉
            sand &= ~(s & sor);
            sor |= s;

            if (str[j][i] != '-') drawn |= state[j][i];
        }
        // 如果某个字母不能出现在任何一个位置，则无解
        if (sor != (1 << N) - 1) {
            memcpy(state, bstate[kcnt], sizeof state);
            memcpy(str, bstr[kcnt], sizeof str);
            return false;
        }
        // 如果某个字母，只能在一个位置上，则直接填
        for (int j = sand; j; j -= j & -j) {
            int t = j & -j;
            if (!(drawn & t)) {
                // 找到对应的位置 k，t 代表的字母只能在 k 处出现
                for (int k = 0; k < N; k++) {
                    if (state[k][i] & t) {
                        draw(k, i, log[t]);
                        cnt--;
                    }
                }
            }
        }
    }

    // 对于每一16宫格，如果某个字母不能出现在任何一个位置，则无解
    // 如果某个字母，只能在一个位置上，则直接填
    // i 枚举的是九宫格 0-15 的编号（从上往下，每行从左往右）
    for (int i = 0; i < N; i++) {
        // sor 表示整个16宫格所有候选字母
        // sand 表示只能在某个位置的那些数
        int sor = 0, sand = (1 << N) - 1;
        // 这一16宫格上已经填过的字母
        int drawn = 0;
        // j 枚举的是一个格子内元素 0-15 的编号（从上往下，每行从左往右）
        for (int j = 0; j < N; j++) {
            int sx = i / 4 * 4, sy = i % 4 * 4;
            int dx = j / 4, dy = j % 4;
            int s = state[sx + dx][sy + dy];
            // 如果既能在前面备选，又能在当前备选，就从 sand 去掉
            sand &= ~(s & sor);
            sor |= s;

            if (str[sx + dx][sy + dy] != '-') drawn |= state[sx + dx][sy + dy];
        }
        // 如果某个字母不能出现在任何一个位置，则无解
        if (sor != (1 << N) - 1) {
            memcpy(state, bstate[kcnt], sizeof state);
            memcpy(str, bstr[kcnt], sizeof str);
            return false;
        }
        // 如果某个字母，只能在一个位置上，则直接填
        for (int j = sand; j; j -= j & -j) {
            int t = j & -j;
            if (!(drawn & t)) {
                // 找到对应的位置 k，t 代表的字母只能在 k 处出现
                for (int k = 0; k < N; k++) {
                    int sx = i / 4 * 4, sy = i % 4 * 4;
                    int dx = k / 4, dy = k % 4;
                    if (state[sx + dx][sy + dy] & t) {
                        draw(sx + dx, sy + dy, log[t]);
                        cnt--;
                    }
                }
            }
        }
    }

    if (cnt == 0) return true;

    // 每次选择备选方案最少的格子来填
    int x, y, s = 100;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (str[i][j] == '-' && ones[state[i][j]] < s) {
                s = ones[state[i][j]];
                x = i, y = j;
            }
        }
    }
    // 枚举这个位置填哪个数字
    memcpy(bstate2[kcnt], state, sizeof state);
    for (int i = state[x][y]; i; i -= i & -i) {
        memcpy(state, bstate2[kcnt], sizeof state);
        draw(x, y, log[i & -i]);
        if (dfs(cnt - 1)) return true;
    }

    // 失败：恢复现场
    memcpy(state, bstate[kcnt], sizeof state);
    memcpy(str, bstr[kcnt], sizeof str);
    return false;
}
int main() {
    for (int i = 0; i < N; i++) log[1 << i] = i;
    for (int i = 0; i < 1 << N; i++) {
        for (int j = i; j; j -= j & -j) {
            ones[i]++;
        }
    }

    while (cin >> str[0]) {
        for (int i = 1; i < N; i++) cin >> str[i];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                state[i][j] = (1 << N) - 1;
            }
        }

        int cnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (str[i][j] != '-') {
                    draw(i, j, str[i][j] - 'A');
                } else
                    cnt++;
            }
        }
        dfs(cnt);

        for (int i = 0; i < N; i++) {
            cout << str[i] << endl;
        }
        cout << endl;
    }
    return 0;
}