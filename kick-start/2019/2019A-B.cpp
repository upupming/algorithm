#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
#define inf 0x3fffffff

int t, r, c, mh[260][260];
// r, c, distance
queue<pair<int, int>> sources;
int R[4] = { 0, 0, 1, -1};
int C[4] = { 1, -1, 0, 0};

// given a value of K, can we add a new delivery office so that the maximum delivery time is at most K
bool ok(int k) {
    // dist((x1, y1), (x2, y2))
    // = |x1 - x2| + |y1 - y2|，注意到time相等的点组成斜45度正方形
    // = max(|x1 + y1 - (x2 + y2)|, |x1 - y1 - (x2 - y2)|)
    // 就是两种情况，分别是形成斜率为正、斜率为负的直线时的情况
    int minX1PlusY1 = inf, maxX1PlusY1 = -inf;
    int minX1MinusY1 = inf, maxX1MinusY1 = -inf;
    int cnt = 0;
    // O(RC)
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            // 找到所有当前不满足 <= k 的点
            if (mh[i][j] > k) {
                cnt++;
                minX1PlusY1 = min(minX1PlusY1, i + j);
                maxX1PlusY1 = max (maxX1PlusY1, i + j);
                minX1MinusY1 = min(minX1MinusY1, i - j);
                maxX1MinusY1 = max(maxX1MinusY1, i - j);
            }
        }
    }
    if (cnt == 0) return true;
    // O(RC)
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            // 选择 (i, j) 新建 delivery
            int x = max(abs(minX1PlusY1 - (i + j)), abs(maxX1PlusY1 - (i + j)));
            int y = max(abs(minX1MinusY1 - (i - j)), abs(maxX1MinusY1 - (i - j)));
            int dist = max(x, y);
            if (dist <= k) return true;
        }
    }
    return false;
}

void print(int mh[][260] = mh) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << " " << mh[i][j];
        }
        cout << endl;
    }
}

int solve() {
    // O(RC) multiple sources bfs: calculate manhattan distance matrix
    while (!sources.empty()) {
        pair<int, int> tmp = sources.front();
        sources.pop();
        for (int i = 0; i < 4; i++) {
            int rr = tmp.first + R[i];
            int cc = tmp.second + C[i];
            int dist = mh[tmp.first][tmp.second] + 1;
            if (rr >= 0 && rr < r && cc >= 0 && cc < c && mh[rr][cc] > dist) {
                mh[rr][cc] = dist;
                sources.push(make_pair(rr, cc));
            }
        }
    }

    // print();
    // O(RClog(R+C))Binary search, RC is for ok function
    // 找到最小的 k
    int low = 0, high = 2 * (r + c), i = r + c;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (ok(mid)) {
            // cout << "ok: " << mid << endl;
            i = mid;
            high = mid - 1;
        } else {
            // cout << "not ok: " << mid << endl;
            low = mid + 1;
        }
    }
    return i;
}

int main() {
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        cin >> r >> c;
        fill(mh[0], mh[0] + 260 * 260, inf);
        for (int i = 0; i < r; i++) {
            string str;
            cin >> str;
            for (int j = 0; j < c; j++) {
                if (str[j] == '1') {
                    sources.push(make_pair(i, j));
                    mh[i][j] = 0;
                }
            }
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}

