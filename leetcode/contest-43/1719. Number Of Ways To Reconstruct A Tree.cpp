#include <bits/stdc++.h>
using namespace std;

// https://www.acwing.com/activity/content/code/content/679749/

/*
对于数对 `[x, y]`，如果存在 `z` 使得 `[x, z]` 在 `pairs` 中出现过，但是 `[y, z]` 没有在 `pairs` 中出现过，那么可以断定 `x` 一定是 `y` 的祖先，且 z 在 x 的不同于 y 的后代分支上，例如：

```
  x
 / \
y   z
```

按照上述性质，可以令 `g2[x][y] = true` 表示一定要将 x 作为 y 的祖先

`g[x][y] = true` 初始化为表示 `[x, y]`/`[y, x]` 在 `pairs` 中出现过。

易知答案情况：

- `g[x][y] && g2[x][y] && g2[y][x]`: 0
- `g[x][y] && !g2[x][y] && !g2[y][x]`: 2
- 其他：1
*/

const int N = 510;
class Solution {
    bool g[N][N], g2[N][N];
    int id[N], n;

   public:
    int checkWays(vector<vector<int>>& pairs) {
        memset(g, false, sizeof(g));
        memset(g2, false, sizeof(g2));
        memset(id, 0, sizeof(id));
        n = 0;
        for (vector<int>& pr : pairs) {
            // 离散化，将输入映射成一段连续的 id
            int x = pr[0], y = pr[1];
            if (!id[x]) id[x] = ++n;
            if (!id[y]) id[y] = ++n;
            // g 表示存在 pair 关系
            g[id[x]][id[y]] = g[id[y]][id[x]] = true;
        }
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= n; y++) {
                if (g[x][y]) {
                    // 寻找存不存在 z，满足存在 [x, z] 但是不存在 [y, z]
                    for (int z = 1; z <= n; z++) {
                        if (z == x || z == y) continue;
                        if (g[x][z] && !g[y][z]) {
                            // 找到了，要将 g2[x][y] 设置为 true
                            // 如果同时存在 g2[y][x]，是不可能满足的
                            if (g2[y][x]) return 0;
                            g2[x][y] = true;
                            break;
                        }
                    }
                }
            }
        }
        for (int x = 1; x <= n; x++)
            for (int y = 1; y <= n; y++)
                // [x, y] 出现过，且 x->y, y->x 均可，答案至少为 2
                if (x != y && g[x][y] && !g2[x][y] && !g2[y][x])
                    return 2;
        return 1;
    }
};