#include <bits/stdc++.h>
using namespace std;
const int N = 2e4 + 10, M = 8e4 + 10;
int d[N], v[N];
int head[N], ver[M], edge[M], Next[M], tot;
int n, cnt[N];
const int mod = 1e9 + 7;

// 加入有向边 (x, y)，权值为 z
void add(int x, int y, int z) {
    // 真实数据
    ver[++tot] = y, edge[tot] = z;
    // 在表头 x 处插入
    Next[tot] = head[x], head[x] = tot;
}

// 堆优化：O(M log N)，适用于 N 比较大的情况
void dijkstra() {
typedef pair<int, int> PII;
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    memset(d, 0x3f, sizeof d);
    d[n] = 0;
    pq.push({0, n});
    while (pq.size()) {
        // 取出堆顶
        int x = pq.top().second;
        pq.pop();
        if (v[x]) continue;
        v[x] = 1;
        // 扫描所有出边
        for (int i = head[x]; i; i = Next[i]) {
            int y = ver[i], z = edge[i];
            if (d[y] > d[x] + z) {
                d[y] = d[x] + z;
                pq.push({d[y], y});
            }
        }
    }
}

bool cmp(int a, int b) {
    return d[a] < d[b];
}

class Solution {
   public:
    int countRestrictedPaths(int _n, vector<vector<int>>& edges) {
        n = _n;
        memset(v, 0, sizeof v);
        memset(head, 0, sizeof head);
        memset(ver, 0, sizeof ver);
        memset(edge, 0, sizeof edge);
        memset(Next, 0, sizeof Next);
        tot = 0;
        memset(cnt, 0, sizeof cnt);
        for (auto& e : edges) {
            add(e[0], e[1], e[2]);
            add(e[1], e[0], e[2]);
        }
        dijkstra();

        vector<int> v;
        for (int i = 1; i <= n; i++) {
            v.push_back(i);
        }
        sort(v.begin(), v.end(), cmp);
        cnt[n] = 1;
        // 类似 dp 思想
        // 求 cnt[x]，在所有 d 较小的 cnt 计算完毕之后，才可以计算 cnt[x]，因此上面对 v 进行了排序
        for (int x : v) {
            // 扫描所有出边
            for (int i = head[x]; i; i = Next[i]) {
                int y = ver[i];
                if (d[x] > d[y])
                    cnt[x] = (cnt[x] + cnt[y]) % mod;
            }
        }
        // cnt[i] 表示从 i 到 n 的满足条件的路径数量
        return cnt[1];
    }
};
