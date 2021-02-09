/*
f[b1][b2][b3][b4]: 所有第 i 种卡片使用了 bi 张的走法的最大分值
f[b1][b2][b3][b4] 的所有走法按照最后一步选择哪张卡片分成四类
第 i 类为最后一步选择第 i 种卡片
比如 i = 2，则这一类的最大分值是：
    f[b1][b2-1][b3][b4] + score[b1 + 2b2 + 3b3 + 4b4]
时间复杂度：(40^4)
*/
#include <iostream>
using namespace std;
const int N = 360, M = 41;

int n, m, score[N], f[M][M][M][M], t;
int main() {
    int b[5] = {0};
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> score[i];
    for (int i = 0; i < m; i++) {
        cin >> t;
        b[t]++;
    }
    for (int A = 0; A <= b[1]; A++)
        for (int B = 0; B <= b[2]; B++)
            for (int C = 0; C <= b[3]; C++)
                for (int D = 0; D <= b[4]; D++) {
                    int s = score[A + B * 2 + C * 3 + D * 4];
                    int &v = f[A][B][C][D];
                    v = s;
                    if (A) v = max(v, f[A - 1][B][C][D] + s);
                    if (B) v = max(v, f[A][B - 1][C][D] + s);
                    if (C) v = max(v, f[A][B][C - 1][D] + s);
                    if (D) v = max(v, f[A][B][C][D - 1] + s);
                }
    cout << f[b[1]][b[2]][b[3]][b[4]] << endl;
    return 0;
}