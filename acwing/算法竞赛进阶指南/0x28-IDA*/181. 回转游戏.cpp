/*
DFS 搜索：
在每个状态下枚举执行哪种操作，然后沿着该分支深入即可。
剪枝：记录上一次的操作不执行上次操作的逆操作，避免来回搜素。
IDA*:
1. 迭代加深，从 1 开始从小到大依次限制操作次数（有可能初始状态就满足，所以实际代码里面一般都是从 0 开始）
2. 估价函数：在每个状态下，如果中间 8 个格子里出现次数最多的数字是 k，剩下有 m 个与 k 不同，那么把这中间 8 个格子里的数字都变成 k 至少需要 m 次操作。因此以这个 m 为估价即可

思考一下怎么表示每个状态最简洁？感觉直接用一个 7 * 7 的二维数组是比较好的，这样 shift 移动操作的时候方便处理一些，就是输入输出会复杂一些
可优化的点：y 总用的一维数组存的，然后对操作进行打表，代码会简洁很多
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 7;

int a[N][N], e, k;
int center[8][2] = {
    {2, 2},
    {2, 3},
    {2, 4},
    {3, 2},
    {3, 4},
    {4, 2},
    {4, 3},
    {4, 4},
};
string ans;

// 把这中间 8 个格子里的数字都变成 k 至少需要 m 次操作
int getM() {
    int cnt[4] = {0};
    for (int i = 0; i < 8; i++) {
        cnt[a[center[i][0]][center[i][1]]]++;
    }
    k = 1;
    for (int i = 2; i <= 3; i++) {
        if (cnt[i] > cnt[k]) k = i;
    }
    int m = 0;
    for (int i = 0; i < 8; i++) {
        if (a[center[i][0]][center[i][1]] != k) m++;
    }
    return m;
}
void out() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
// last 表示上一次操作，避免来回搜素
bool dfs(int dep, char last) {
    int m = getM();
    if (m == 0) {
        if (e == 0)
            cout << "No moves needed" << endl;
        else
            cout << ans << endl;
        cout << k << endl;
        return true;
    }
    if (dep + m >= e) return false;

    // 最好用局部变量避免 dfs 时候被其他层篡改数据
    int cpy[N][N];
    string tmp = ans;
    // 枚举所有的移动方式
    if (last != 'F') {
        ans += 'A';
        memcpy(cpy, a, sizeof(a));
        // 对于所有的行
        for (int i = 0; i < N; i++) {
            a[i][2] = cpy[(i + 1) % N][2];
        }
        if (dfs(dep + 1, 'A')) return true;
        // 还原现场
        memcpy(a, cpy, sizeof(a));
        ans = tmp;
    }
    if (last != 'E') {
        ans += 'B';
        memcpy(cpy, a, sizeof(a));
        // 对于所有的行
        for (int i = 0; i < N; i++) {
            a[i][4] = cpy[(i + 1) % N][4];
        }
        if (dfs(dep + 1, 'B')) return true;
        // 还原现场
        memcpy(a, cpy, sizeof(a));
        ans = tmp;
    }
    if (last != 'H') {
        ans += 'C';
        memcpy(cpy, a, sizeof(a));
        // 对于所有的列
        for (int i = 0; i < N; i++) {
            a[2][i] = cpy[2][(i - 1 + N) % N];
        }
        if (dfs(dep + 1, 'C')) return true;
        // 还原现场
        memcpy(a, cpy, sizeof(a));
        ans = tmp;
    }
    if (last != 'G') {
        ans += 'D';
        memcpy(cpy, a, sizeof(a));
        // 对于所有的列
        for (int i = 0; i < N; i++) {
            a[4][i] = cpy[4][(i - 1 + N) % N];
        }
        if (dfs(dep + 1, 'D')) return true;
        // 还原现场
        memcpy(a, cpy, sizeof(a));
        ans = tmp;
    }
    if (last != 'B') {
        ans += 'E';
        memcpy(cpy, a, sizeof(a));
        // 对于所有的行
        for (int i = 0; i < N; i++) {
            a[i][4] = cpy[(i - 1 + N) % N][4];
        }
        if (dfs(dep + 1, 'E')) return true;
        // 还原现场
        memcpy(a, cpy, sizeof(a));
        ans = tmp;
    }
    if (last != 'A') {
        ans += 'F';
        memcpy(cpy, a, sizeof(a));
        // 对于所有的行
        for (int i = 0; i < N; i++) {
            a[i][2] = cpy[(i - 1 + N) % N][2];
        }
        if (dfs(dep + 1, 'F')) return true;
        // 还原现场
        memcpy(a, cpy, sizeof(a));
        ans = tmp;
    }
    if (last != 'D') {
        ans += 'G';
        memcpy(cpy, a, sizeof(a));
        // 对于所有的列
        for (int i = 0; i < N; i++) {
            a[4][i] = cpy[4][(i + 1) % N];
        }
        if (dfs(dep + 1, 'G')) return true;
        // 还原现场
        memcpy(a, cpy, sizeof(a));
        ans = tmp;
    }
    if (last != 'C') {
        ans += 'H';
        memcpy(cpy, a, sizeof(a));
        // 对于所有的列
        for (int i = 0; i < N; i++) {
            a[2][i] = cpy[2][(i + 1) % N];
        }
        if (dfs(dep + 1, 'H')) return true;
        // 还原现场
        memcpy(a, cpy, sizeof(a));
        ans = tmp;
    }

    return false;
}
int main() {
    int x;
    while (cin >> x && x) {
        a[0][2] = x;
        for (int i = 1; i <= 23; i++) {
            cin >> x;
            if (i == 1) a[0][4] = x;
            if (i == 2) a[1][2] = x;
            if (i == 3) a[1][4] = x;
            if (i >= 4 && i <= 10) a[2][i - 4] = x;
            if (i == 11) a[3][2] = x;
            if (i == 12) a[3][4] = x;
            if (i >= 13 && i <= 19) a[4][i - 13] = x;
            if (i == 20) a[5][2] = x;
            if (i == 21) a[5][4] = x;
            if (i == 22) a[6][2] = x;
            if (i == 23) a[6][4] = x;
        }

        e = 0;
        while (true) {
            ans = "";
            if (dfs(0, ' ')) break;
            e++;
        }
    }
    return 0;
}
