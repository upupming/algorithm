#include <bits/stdc++.h>
using namespace std;
const int N = 310;

int t;
typedef long long LL;
LL pos[N][2], n, s[2];

LL orientation(LL p[2], LL q[2], LL r[2]) {
    return (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
}
typedef pair<LL, LL> PLL;

LL orientation(PLL p, PLL q, LL r[2]) {
    return (q.second - p.second) * (r[0] - q.first) - (q.first - p.first) * (r[1] - q.second);
}

double dist(PLL p, PLL q) {
    auto a = p.first - q.first, b = p.second - q.second;
    // cout << "(" << p.first << ", " << p.second << "); "
    //      << "(" << q.first << ", " << q.second << "); "
    //      << a << " " << b << endl;
    return sqrt(a * a + b * b);
}

void solve() {
    cin >> n;
    int leftMost = 0;
    for (int i = 0; i < n; i++) {
        cin >> pos[i][0] >> pos[i][1];
        if (pos[i][0] < pos[leftMost][0]) {
            leftMost = i;
        }
    }
    cin >> s[0] >> s[1];

    int p = leftMost;
    vector<PLL> poly;
    do {
        int q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (orientation(pos[p], pos[i], pos[q]) < 0) {
                q = i;
            }
        }
        priority_queue<pair<double, PLL>, vector<pair<double, PLL>>, greater<>> pq;
        // 如果有一些是 between 的，也要加上
        for (int i = 0; i < n; i++) {
            if (i != p && i != q && orientation(pos[p], pos[q], pos[i]) == 0) {
                // 按照顺序加入
                pq.push({double(pos[i][0] - pos[p][0]) / (pos[q][0] - pos[p][0]),
                         make_pair(pos[i][0], pos[i][1])});
            }
        }
        while (pq.size()) {
            poly.push_back(pq.top().second);
            pq.pop();
        }
        poly.push_back({pos[q][0], pos[q][1]});
        p = q;
    } while (p != leftMost);

    int m = poly.size();
    if (m <= 2) {
        puts("IMPOSSIBLE");
        return;
    }
    bool ok = true;
    LL o0 = orientation(poly[0], poly[1], s);
    int dest = o0 > 0;
    if (o0 == 0) ok = false;
    // cout << "o0: " << o0 << endl;
    // 如果点不在凸包内，就不可能了
    for (int i = 1; ok && i < m; i++) {
        LL tmp = orientation(poly[i], poly[(i + 1) % m], s);
        if (tmp == 0 || (dest ^ (tmp > 0))) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        puts("IMPOSSIBLE");
        return;
    }
    // 逐渐缩小凸包
    double ans = 0;
    for (int i = 0; i < m; i++) {
        ans += dist(poly[i], poly[(i + 1) % m]);
        // cout << dist(poly[i], poly[(i + 1) % m]) << " " << ans << endl;
    }
    // cout << "ans: " << ans << endl;
    // 这里坍缩算法有点问题，算出来不是最小值
    while (poly.size() > 3) {
        int m = poly.size();
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
        for (int i = 0; i < m; i++) {
            int prev = (i - 1 + m) % m, next = (i + 1) % m;
            int tmp = orientation(poly[prev], poly[next], s);
            if (tmp == 0 || (dest ^ (tmp > 0))) continue;
            pq.push({dist(poly[prev], poly[i]) + dist(poly[next], poly[i]) - dist(poly[prev], poly[next]), i});
        }
        if (pq.size()) {
            poly.erase(poly.begin() + pq.top().second);
            ans -= pq.top().first;
            // cout << pq.top().second << " " << pq.top().first << " " << ans << endl;
        } else {
            break;
        }
    }
    printf("%.8f\n", ans);
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
