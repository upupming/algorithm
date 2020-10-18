#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

long long t, w, n, x[100010], sum[100010];

// 是否一定就是变成现在存在的某个数？
// 比如 1 2 100000，N 为 200000000，这个时候可以都变成 2
// 1 2 100000 100000
//      50000 * 4 vs. 100000 * 2
// 可以验证，一定是都变成现存的某个数，否则的话可以把部步数转义之后会等价的
// 如何计算任意两个数之间的距离？ min(直接距离 d1，转折距离 d2)

// 优化，先排序
// 2 9 3 8
// 2 3 8 9
// 给定 8，很快就能求距离
// 算出第一个 min 是转折距离的左右点
// 因为 N = 10
// dist (2, 8) = 1, 10, 9, 8 = 4 = 2 + 10 - 8
// d1 (x, 8) = 8 - x
// d2 (x, 8) = x + N - 8
// d1 == d2 求出 x = (16 - N) / 2 （<=）
// 算出分界线 x ，之后分界线左边的全部用 d2 公式，右边的全部用 d1 公式
// 都需要求前缀和方便计算

// d1 = x - 2
// 10, 1, 2
// d2 = 2 + (n - x) = 3
// 求出 x = (n + 4) / 2
// 2 3 8 9
// 0 1 2 3
// 7
// [2][3][89]

// d1 = |x - 8|
// d2 = n + (-|x - 8|)

// 2 3 4
// 3 - 2
// 4 - 3

/**
1
3 100000
1 2 100000
*/

long long solve() {
    long long ans = __LONG_LONG_MAX__;
    for (int i = 0; i < w; i++) {
        // cout << "i: " << i << endl;

        long long dest = x[i];
        long long boundary = (2 * dest - n) / 2;
        if (boundary <= 0) {
            // cout << "if (boundary < 0) {" << endl;
            boundary = (2 * dest + n) / 2;

            // cout << "dest: " << dest << endl;
            // cout << "boundary: " << boundary << endl;

            // int j = upper_bound(x, x + w, boundary) - x;
            // cout << "j: " << j << endl;
            // long long part1 = sum[j] - dest * j;
            // long long part2 = (dest + n) * (w - j) - (sum[w] - sum[j]);
            // cout << "test 1: " << part1 << endl;
            // cout << "test 2: " << part2 << endl;
            // long long changes = abs(part1) + abs(part2);

            // cout << "changes: " << changes << endl;
            // ans = min(ans, changes);
            // cout << "ans: " << ans << endl;
        }
        // // 先考虑 boundary >= 0 的情况
        // else {
        //     cout << "dest: " << dest << endl;
        //     cout << "boundary: " << boundary << endl;

        //     int j = upper_bound(x, x + w, boundary) - x;
        //     cout << "j: " << j << endl;
        //     long long part1 = dest * j - sum[j];
        //     long long part2 = sum[w] - sum[j] - (dest + n) * (w - j);
        //     cout << "test 1: " << part1 << endl;
        //     cout << "test 2: " << part2 << endl;
        //     long long changes = abs(part1) + abs(part2);

        //     cout << "changes: " << changes << endl;
        //     ans = min(ans, changes);
        //     cout << "ans: " << ans << endl;
        // }

        // cout << "dest: " << dest << endl;
        // cout << "boundary: " << boundary << endl;

        int j = upper_bound(x, x + w, boundary) - x;
        // cout << "j: " << j << endl;
        long long part1, part2, part3;

        int ib = i + 1;
        if (j < ib) {
            // 0 - j, j - i, i - w
            // special
            part1 = sum[j] + (n - dest) * j;
            part2 = dest * (ib - j) - (sum[ib] - sum[j]);
            part3 = (sum[w] - sum[ib]) - dest * (w - ib);
        } else {
            // 0 - i, i - j, j - w
            part1 = dest * ib - sum[ib];
            part2 = (sum[j] - sum[ib]) - dest * (j - ib);
            // special
            part3 = -(sum[w] - sum[j]) + (n + dest) * (w - j);
        }

        // part1 = sum[j] - dest * j;
        // part2 = (dest + n) * (w - j) - (sum[w] - sum[j]);

        // cout << "test 1: " << part1 << endl;
        // cout << "test 2: " << part2 << endl;
        // cout << "test 3: " << part3 << endl;
        long long changes = abs(part1) + abs(part2) + abs(part3);

        // cout << "changes: " << changes << endl;
        ans = min(ans, changes);
        // cout << "ans: " << ans << endl;
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> w >> n;
        sum[0] = 0;
        for (int i = 0; i < w; i++) {
            cin >> x[i];
        }
        sort(x, x + w);
        for (int i = 0; i < w; i++) {
            sum[i + 1] = sum[i] + x[i];
        }
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}