#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// TODO: fix this answer

int t, n, m, k, a[100];

// if a construction is okay
bool ok(const map<int, int>& groups) {
    if (groups.size() != k) return false;
    vector<int> b;
    for (auto g : groups) {
        b.push_back(g.second);
    }
    sort(b.begin(), b.end());

    for (int i = 0; i < b.size(); i++) {
        cout << " " << b[i];
    }
    cout << endl;

    for (int i = 0; i < k; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

double dfs(map<int, int>& groups, int depth) {
    if (depth == n + 1) {
        if (ok(groups))
            return m;
        else
            return 0;
    }
    double sum;
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        groups[i]++;
        double val = dfs(groups, depth + 1);
        if (val > 0) {
            cnt++;
            sum += val;
        }
        groups[i]--;
    }
    return cnt ? (sum / cnt + 1) : 1;
}

double solve() {
    map<int, int> groups;
    return dfs(groups, 1);
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> m >> k;
        for (int i = 0; i < k; i++) cin >> a[i];

        printf("Case #%d: %lf\n", i, solve());
    }
    return 0;
}