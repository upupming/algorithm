#include <iostream>
using namespace std;
const int N = 1e3 + 10;
typedef long long LL;

int t, g[N][N], r, c, sumR[N][N], sumC[N][N];

int dl[] = {0, -1, 0, -1, -2, 0, -2, 0};
int dr[] = {1, 0, 1, 0, 0, 2, 0, 2};
int du[] = {-2, -2, 0, 0, -1, -1, 0, 0};
int dd[] = {0, 0, 2, 2, 0, 0, 1, 1};

bool valid(int i, int j, int x, int dir) {
    int left = j;
    if (dl[dir] > 0)
        left = j + x * dl[dir] - 1;
    else if (dl[dir] < 0)
        left = j + x * dl[dir] + 1;

    int right = j;
    if (dr[dir] > 0)
        right = j + x * dr[dir] - 1;
    else if (dr[dir] < 0)
        right = j + x * dr[dir] + 1;

    int up = i;
    if (du[dir] > 0)
        up = i + x * du[dir] - 1;
    else if (du[dir] < 0)
        up = i + x * du[dir] + 1;

    int down = i;
    if (dd[dir] > 0)
        down = i + x * dd[dir] - 1;
    else if (dd[dir] < 0)
        down = i + x * dd[dir] + 1;

    if (up < 1 || right > c || left < 1 || down > r) return false;
    int h = abs(sumR[i][right] - sumR[i][left - 1]);
    int v = abs(sumC[j][down] - sumC[j][up - 1]);
    return ((h == x) &&
            (v == 2 * x)) ||
           ((h == 2 * x) &&
            (v == x));
}

LL calc(int dir) {
    LL ans = 0;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            int l = 0, right = max(r, c);
            while (l < right) {
                int mid = (l + right + 1) >> 1;
                if (valid(i, j, mid, dir)) {
                    l = mid;
                } else {
                    right = mid - 1;
                }
            }
            if (l < 2) continue;
            ans += l - 1;
        }
    }
    return ans;
}

LL solve() {
    LL ans = 0;
    for (int i = 0; i < 8; i++) {
        ans += calc(i);
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> r >> c;
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                cin >> g[i][j];
                sumR[i][j] = sumR[i][j - 1] + g[i][j];
                sumC[j][i] = sumC[j][i - 1] + g[i][j];
            }
        }
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
