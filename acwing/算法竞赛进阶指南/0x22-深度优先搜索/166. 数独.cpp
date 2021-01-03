/*
状态：每个位置填上了什么数
分支：找出一个还没有填数的位置，检查有哪些合法的数字可以填
搜索边界：所有位置都被填满 或者 某个位置没有合法数字可以填
优化策略：选择能填的合法数字最少的位置
位运算：每行、每列、每个九宫格分别用一个 9 位二进制数保存那些数字还可以填，对于每个位置，把它所在的行、列、九宫格的 3 个二进制数做与运算，就可以得到该位置能填哪些数，用 lowbit 运算可以把能填的数字取出。当一个位置填上某些数后，把该位置所在的行、列、九宫格记录的二进制数的对应位改为 0，即可更新当前状态，回溯时改回 1 即可还原现场。
*/
#include <bitset>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
const int N = 9;

// 第 i 行、列、九宫格可以填的数的 bit 表示
// h[2^i] = i，cnt[i] = i 有多少个 1，
// bitset 不支持 lowbit 运算，因此转为直接使用 int
int row[N], col[N], cell[N], h[1 << N], cnt[1 << N];
string s;
inline void flip(int x, int y, int z) {
    row[x] ^= 1 << z;
    col[y] ^= 1 << z;
    cell[x / 3 * 3 + y / 3] ^= 1 << z;
}
void print() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << s[i * N + j];
        }
    }
    cout << endl;
}
bool dfs(int now) {
    // 终止条件1：所有位置都被填满
    if (now == 0) {
        // 输出答案
        print();
        return true;
    }
    // 找一个能填的合法数字最少的位置
    int minCh = 10, x, y;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (s[i * 9 + j] == '.') {
                auto choiceBits = row[i] & col[j] & cell[i / 3 * 3 + j / 3];
                // 终止条件2：某个位置没有合法数字可以填
                int numCh = cnt[choiceBits];
                if (numCh == 0) return false;
                if (numCh < minCh) {
                    minCh = numCh;
                    x = i, y = j;
                }
            }
        }
    }

    // 枚举当前位置所有的填充方法
    auto choiceBits = row[x] & col[y] & cell[x / 3 * 3 + y / 3];
    for (int val = choiceBits; val; val -= val & -val) {
        int num = h[val & -val];
        s[x * N + y] = num + '1';
        flip(x, y, num);
        if (dfs(now - 1)) return true;
        // 恢复现场，既然可以填 num，对应位初始状态都是 1
        flip(x, y, num);
        s[x * N + y] = '.';
    }
    return false;
}
int main() {
    for (int i = 0; i < N; i++)
        h[1 << i] = i;
    for (int i = 0; i < 1 << N; i++) {
        for (int j = i; j; j -= j & -j) {
            cnt[i]++;
        }
    }

    while (cin >> s && s != "end") {
        // 空白待填的个数
        int tot = 0;
        // 初始时，1~9 都可以填
        for (int i = 0; i < N; i++) {
            row[i] = col[i] = cell[i] = (1 << N) - 1;
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (s[i * N + j] == '.') {
                    tot++;
                    continue;
                }
                flip(i, j, s[i * N + j] - '1');
            }
        }
        dfs(tot);
    }
    return 0;
}