#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>

using namespace std;

int t, n, k, m[100005];
// 缓存 dfs 结果
map<int, map<int, int>> mp;

int diff(int d, int k) {
    return int(ceil(d / (k + 1.0)));
}

int dfs(int workout_idx, int k) {
    if (mp.count(workout_idx) && mp[workout_idx].count(k)) {
        return mp[workout_idx][k];
    }

    // 总共 n - 1 个间隔
    if (workout_idx == n - 1 - 1) {
        return mp[workout_idx][k] = diff(m[workout_idx], k);
    }

    int res = INT32_MAX;
    // i 表示用 i 个新的锻炼来划分原有的锻炼
    for (int i = 0; i <= k; i++) {
        int tmp = diff(m[workout_idx], i);

        int sub_value = dfs(workout_idx + 1, k - i);
        // 后面的所有插入情况中，取最优情况
        res = min(res, max(tmp, sub_value));

        // 剪枝：再给此处增加锻炼数没用了，只会造成偏斜越来越严重
        if (tmp <= sub_value) break;
    }

    mp[workout_idx][k] = res;
    return res;
}

int solve() {
    return dfs(0, k);
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        mp.clear();
        cin >> n >> k;
        int prev, cur;
        for (int i = 0; i < n; i++) {
            cin >> cur;
            if (i != 0) {
                m[i - 1] = cur - prev;
            }
            prev = cur;
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}