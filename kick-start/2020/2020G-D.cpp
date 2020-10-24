#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int t, n;
// int will overflow when accumulating
vector<long long> a, sum;
double dp[5050][5050],
    // horizontal & vertical sum
    dphs[5050], dpvs[5050];
map<int, map<int, double>> m;

void print() {
    cout << "array a: ";
    for (auto it = a.begin(); it < a.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

/**
Case 1:
    2 1 10
      3 10: 3
        13: 13
        sum: 16

    2 11: 11
      13: 13
      sum: 24

    average: (16 + 24) /2 = 20
 */

/**
Solution 1:
    brute force all possible combination each step
    most naive method takes (n -1)! time; can pass test set 1 only

    1. depth = 0, ans = [(3 + x) + (y + 11)] / 2
    2. solve depth 1 for x (3 11): ans = (14 + z) / 2
    3. solve depth 2 for z (14): ans = 14
 */
double dfs(int depth) {
    // cout << "dfs(int depth): " << depth << endl;
    // print();

    if (depth == n - 1 - 1) {
        // cout << "dfs(int depth), ans: " << n - 1 << ", " << (a[0] + a[1]) << endl;
        return a[0] + a[1];
    }

    double ans = 0;
    // all possible combinations
    for (int i = 0; i < n - 1 - depth; i++) {
        // merge a[i] and a[i+1] to a single value
        long long tmp1 = a[i], tmp2 = a[i + 1];
        a[i + 1] = a[i] + a[i + 1];
        ans += a[i + 1];
        // cout << "ans += sum: " << a[i + 1] << endl;
        a.erase(a.begin() + i);

        double v = dfs(depth + 1);
        // cout << "ans += dfs: " << v << endl;
        ans += v;

        // !important: recovery the original vector
        a.insert(a.begin() + i, tmp1);
        a[i + 1] = tmp2;
    }
    // Average the ans
    ans /= n - 1 - depth;
    // cout << "ans /= dfs: " << n - 1 - depth << endl;

    // cout << "ans: " << ans << endl;
    return ans;
}
double solve1() {
    return dfs(0);
}

/**
Solution 2: dfs with cache or using dynamic programming
    dp array for case 1:
    0 3 x
      0 11
        0

    x = (3 + 11) /2  + sum(a)

    dp[i][j] is the average result for closed-interval a[i...j]
    recurrence relattion:
        dp[i][j] = sum(
                (dp[i][k] + dp[k+1][j]) for all k in [i+1, j - 1)
            ) / (j - i) + sum(a[i...j])

    use prefix sum for optimization to O(n^2) time complexity

    init dp[i][i] to 0
 */

// cache for sum of dp， still cannot pass test 3
double getSumOfDp(int start, int end) {
    if (m.count(start) && m[start].count(end)) {
        return m[start][end];
    }
    double res = 0;
    for (int k = start; k < end; k++) {
        res += dp[start][k] + dp[k + 1][end];
    }
    m[start][end] = res;
    return res;
}

double solve2() {
    for (int i = 0; i < n; i++) {
        dphs[i] = dpvs[i] = 0;
    }
    // dp[i][j] depends all dp[i][k] & dp[k+1][j]
    // d for diagonal index diff (j - i)
    for (int d = 1; d < n; d++) {
        for (int i = 0; i < n - d; i++) {
            int j = d + i;
            // dp[i][j] = 0;
            // for (int k = i; k < j; k++) {
            //     dp[i][j] += dp[i][k] + dp[k + 1][j];
            // }

            // dp[i][j] = getSumOfDp(i, j);

            dp[i][j] = dphs[i] + dpvs[j];

            dp[i][j] = dp[i][j] / d + (sum[j + 1] - sum[i]);

            dphs[i] += dp[i][j];
            dpvs[j] += dp[i][j];
        }
    }

    return dp[0][n - 1];
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        a.clear();
        sum.clear();
        m.clear();
        cin >> n;
        int tmp;
        sum.push_back(0);
        for (int i = 0; i < n; i++) {
            cin >> tmp;
            a.push_back(tmp);
            sum.push_back(sum[i] + a[i]);
        }
        printf("Case #%d: %lf\n", i, solve2());
    }
    return 0;
}