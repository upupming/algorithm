/*
排列形枚举
所有的排列情况，统计一下 r > b 和 r < b 的次数即可，注意可能出现等于的情况
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1010;

int t, n;
int order[N], chosen[N], r[N], b[N], rCnt, bCnt;
// void calc(int k) {
//     if (k == n + 1) {
//         for (int i = 1; i <= n; i++) {
//             if (r[order[i]] > b[order[i]]) {
//                 rCnt++;
//                 return;
//             } else if (r[order[i]] < b[order[i]]) {
//                 bCnt++;
//                 return;
//             }
//         }
//     }
//     for (int i = 1; i <= n; i++) {
//         if (chosen[i]) continue;
//         order[k] = i;
//         chosen[i] = 1;
//         calc(k + 1);
//         chosen[i] = 0;
//         order[k] = 0;
//     }
// }
int main() {
    cin >> t;
    while (t--) {
        memset(chosen, 0, sizeof chosen);
        rCnt = bCnt = 0;
        cin >> n;
        string x, y;
        cin >> x >> y;
        for (int i = 0; i < n; i++) {
            if (x[i] > y[i])
                rCnt++;
            else if (x[i] < y[i])
                bCnt++;
        }
        if (rCnt == bCnt)
            cout << "EQUAL" << endl;
        else if (rCnt > bCnt)
            cout << "RED" << endl;
        else
            cout << "BLUE" << endl;
    }
    return 0;
}