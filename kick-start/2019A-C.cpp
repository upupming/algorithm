// 贪心思想：子问题，每次选最后一个 booking，使得这个 booking 占用座位数最多，可用【交换论证】（exchane argument）证明
// 证明见：https://www.cnblogs.com/Patt/p/11618433.html

// 基本思想:每次取出 【占用座位数最少】的booking

// TODO: 线段树&sweep algorithm太难了，以后有机会好好学一下，现在参考 https://github.com/zouzhitao/competitive-programing/blob/master/kick-start/2019-roundA-contention.cpp 进行实现
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define inf 0x3fffffff

vector<pair<int, int>> book;
int t, n, q;

// O(Q)，判断是否有 k 能满足所有 book 都得到 k 个座位
bool ok(int k) { // k = 
    if (k == 0) return true;
    vector<int> bg(q, 0);
    for (int i = 0; i < q; i++) {
        int sweep_to = max(book[i].first, bg[i]), ed = book[i].second;
        int next_start = ed;
        int cnt = 0;

        for (int j = i + 1; j < q; j++) {
            int l = book[j].first, r = book[j].second;
            if (l > ed) break; // 后续都不用考虑
            if (r <= ed) {
                if (l > sweep_to) cnt += l - sweep_to;
                sweep_to = max(sweep_to, r);
                // book[j] 被满足 k 个以上
                if (cnt >= k) {
                    next_start = l - (cnt - k);
                    break;
                }
            }
        }
        if (cnt < k) {
            cnt += ed - sweep_to;
            if (cnt < k) return false;
            next_start = ed - (cnt - k);
        }
        // Update left start point
        for (int j = i + 1; j < q; j++) {
            int l = book[j].first, r = book[j].second;
            // can book before ith booking
            if (l >= next_start) break;
            // those booking must after ith booking
            if (book[j].second > ed) {
                bg[j] = max(bg[j], ed);
            }
        }
    }
    return true;
}

// O(Q log n)
int solve() {
    sort(book.begin(), book.end()); // (0, 2), (1, 5), (2, 4)
    int low = 0, high = n; // n = 5
    // 找到尽量大的 k ( <= n)，使得所有人能够预定 k 个座位
    while (low <= high) {
        int mid = (low + high) >> 1; // mid = 2
        if (ok(mid)) low = mid + 1;
        else high = mid - 1;
    }
    return low - 1;
}

int main() {
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        scanf("%d%d", &n, &q);
        book.resize(q);
        int l, r;
        for (int i = 0; i < q; i++) {
            scanf("%d%d", &l, &r);
            // 区间从 0 开始，左闭右开
            book[i] = {--l, r};
        }

        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}