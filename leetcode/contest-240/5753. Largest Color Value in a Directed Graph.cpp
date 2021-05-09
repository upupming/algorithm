#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

int tot, ver[N], Next[N], head[N], deg[N];

class Solution {
   public:
    int n, m;
    string colors;
    map<int, vector<int>> cnt;
    void add(int x, int y) {
        ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
        deg[y]++;
    }
    // 拓扑排序模板
    bool topsort() {
        queue<int> q;
        for (int i = 0; i < n; i++) {
            cnt[i].resize(26);
            if (deg[i] == 0) q.push(i);
        }
        int sorted = 0;
        while (q.size()) {
            int x = q.front();
            q.pop();
            // 加上自己的颜色
            cnt[x][colors[x] - 'a']++;
            sorted++;
            for (int i = head[x]; i; i = Next[i]) {
                int y = ver[i];
                // 所有到 y 的前驱中，选择最大的那个
                for (int i = 0; i < 26; i++) {
                    cnt[y][i] = max(cnt[x][i], cnt[y][i]);
                }
                if (--deg[y] == 0) q.push(y);
            }
        }
        // 必须所有点都能够被排序，否则就是存在环
        return sorted == n;
    }
    int largestPathValue(string _colors, vector<vector<int>>& edges) {
        colors = _colors;
        memset(head, 0, sizeof head);
        memset(deg, 0, sizeof deg);
        tot = 0;
        n = colors.length();
        m = edges.size();
        for (auto& e : edges) {
            add(e[0], e[1]);
        }

        if (!topsort()) return -1;

        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 26; j++) {
                ans = max(ans, cnt[i][j]);
            }
        }
        return ans;
    }
};
