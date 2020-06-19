#include <iostream>

using namespace std;

int t, n, k, m[100005], max_diff;
// 单个间隔降到难度 d 至少需要的插入个数
int single_insert_num(int delta_m, int d) {
    int cnt = 0, tmp = 0;
    while (tmp < delta_m) {
        cnt++;
        tmp += d;
    }
    return cnt - 1;
}

// 总体降到难度 d 至少需要的插入个数
int total_insert_num(int d) {
    int res = 0;
    // 总共有 n - 1 个间隔
    for (int i = 0; i < n - 1; i++) {
        res += single_insert_num(m[i], d);
    }
    return res;
}

int solve() {
    int low = 1, high = max_diff, res = max_diff;
    while (low <= high) {
        int mid = (low + high) / 2;
        int k_prime = total_insert_num(mid);
        if (k_prime > k) {
            low = mid + 1;
        } else {
            res = mid;
            high = mid - 1;
        }
    }
    return res;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        max_diff = 0;
        cin >> n >> k;
        int prev, cur;
        for (int i = 0; i < n; i++) {
            cin >> cur;
            if (i != 0) {
                m[i - 1] = cur - prev;
                max_diff = max(max_diff, m[i - 1]);
            }
            prev = cur;
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}