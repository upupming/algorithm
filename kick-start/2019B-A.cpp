#include <iostream>
#include <algorithm>

using namespace std;

int t, n, q, l, r;
string s;
int cntAcc[30][100005];

int solve() {
    // pre-process
    for (int j = 0; j < 26; j++) {
        cntAcc[j][0] = 0;
    }
    for (int i = 1; i <= n; i++) {
        // 注意这里是 i - 1！！！
        int k = s[i - 1] - 'A';
        for (int j = 0; j < 26; j++) {
            if (j == k) cntAcc[j][i] = cntAcc[j][i-1] + 1;
            else cntAcc[j][i] = cntAcc[j][i - 1];
        }
    }
    
    int cnt = 0;
    while (q--) {
        scanf("%d %d", &l, &r);
        int oddCnt = 0;
        for (int j = 0; j < 26; j++) {
            // char j occurrence times in [l, r] (1 based)
            if ((cntAcc[j][r] - cntAcc[j][l - 1]) % 2) oddCnt += 1;
            // if (cntAcc[j][r] - cntAcc[j][l - 1] > 0)
            // cout << (char)(j + 'A') << " " << cntAcc[j][r] - cntAcc[j][l - 1] << ", " << oddCnt << endl;
        }
        if (oddCnt <= 1) cnt++;
    }
    return cnt;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> q >> s;
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}