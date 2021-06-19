#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 2e5 + 10, M = 2 * N;
/*
所有关于有没有环的题目，往往直接使用「拓扑排序」即可
*/
int head[N], ver[M], Next[M], tot, deg[N], cnt, a[N];

// 加入有向边 (x, y)，权值为 z
void add(int x, int y) {
    // 真实数据
    ver[++tot] = y;
    deg[y]++;
    // 在表头 x 处插入
    Next[tot] = head[x], head[x] = tot;
}

int t, n, m;
vector<pair<int, int>> edges;

bool topsort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) q.push(i);
    }
    while (q.size()) {
        auto x = q.front();
        q.pop();
        a[++cnt] = x;
        for (int i = head[x]; i; i = Next[i]) {
            int y = ver[i];
            if (--deg[y] == 0) q.push(y);
        }
    }
    return cnt == n;
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> m;
        edges.clear();
        cnt = tot = 0;
        for (int i = 1; i <= n; i++) {
            head[i] = 0;
            deg[i] = 0;
        }
        for (int i = 1; i <= m; i++) {
            Next[i] = 0;
        }
        for (int i = 1; i <= m; i++) {
            int c, x, y;
            cin >> c >> x >> y;
            if (c == 1) {
                add(x, y);
            } else {
                edges.push_back({x, y});
            }
        }
        if (!topsort()) {
            puts("NO");
        } else {
            puts("YES");
            for (int x = 1; x <= n; x++) {
                for (int i = head[x]; i; i = Next[i]) {
                    int y = ver[i];
                    cout << x << " " << y << endl;
                }
            }
            int pos[n + 1];
            for (int i = 1; i <= n; i++) {
                pos[a[i]] = i;
            }
            for (auto& [x, y] : edges) {
                if (pos[x] > pos[y]) swap(x, y);
                cout << x << " " << y << endl;
            }
        }
    }
    return 0;
}
