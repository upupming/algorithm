// https://www.acwing.com/problem/content/118/
/*
2^16 种可能情况直接用二进制数暴力枚举是否修改某个数
要注意枚举顺序
*/
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

void print(bool a[4][4]) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            cout << " " << a[r][c];
        }
        cout << endl;
    }
    cout << endl;
}
bool a[4][4], b[4][4], change[4][4], cb[4][4], e[4][4];
void relax(bool a[4][4], int r, int c) {
    // 终止下标误写成 r，导致调试了很长时间
    for (int i = 0; i < 4; i++) a[i][c] ^= 1;
    for (int i = 0; i < 4; i++) a[r][i] ^= 1;
    a[r][c] ^= 1;
}
int main() {
    string s;
    for (int i = 0; i < 4; i++) {
        cin >> s;
        for (int j = 0; j < 4; j++) a[i][j] = (s[j] == '-');
    }

    int minCnt = 0x3f3f3f3f;
    for (int i = (1 << 16) - 1; i >= 0; i--) {
        memcpy(b, a, sizeof(a));
        memcpy(change, e, sizeof(e));
        int cnt = 0;

        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                int p = r * 4 + c;
                if ((i >> p) & 1) {
                    change[r][c] = true;
                    relax(b, r, c);
                    cnt++;
                }
            }
        }

        bool ok = true;
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (!b[r][c]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) break;
        }
        if (ok) {
            if (cnt < minCnt) {
                memcpy(cb, change, sizeof(change));
                minCnt = cnt;
            }
        }
    }

    cout << minCnt << endl;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (cb[r][c]) cout << r + 1 << " " << c + 1 << endl;
        }
    }
    return 0;
}