/*
首先过一遍输入里面的相等关系，建立并查集
然后过一遍输入里面的不相等关系，看是不是有不满足的
输入的 i, j 达到 10^9，需要进行离散化；简单起见这里直接用 map 进行离散化（不用书上的数组方法）

也可先建立好图的边关系，用 DFS 搜索每个连通块，给连通块标记值，这种是只支持离做的，而并查集是可以支持在线做的
*/
#include <iostream>
#include <unordered_map>
using namespace std;
const int N = 1e6 + 10;

int t, n, i[N], j[N], e[N], m;
// 离散化
unordered_map<int, int> mp;
int discrete(int x) {
    if (!mp.count(x))
        mp[x] = ++m;
    return mp[x];
}
// 并查集
int fa[N], sz[N];
void init() {
    // 初始化
    for (int i = 1; i <= N; i++) {
        fa[i] = i;
        sz[i] = 1;
    }
}
// Get 操作
int get(int x) {
    if (x == fa[x]) return x;
    // 路径压缩，fa 直接赋值为代表元素
    return fa[x] = get(fa[x]);
}
// Merge 操作
void merge(int x, int y) {
    int fx = get(x), fy = get(y);
    if (fx == fy) return;
    if (sz[fx] < sz[fy]) {
        fa[fx] = fy;
        sz[fy] += sz[fx];
    } else {
        fa[fy] = fx;
        sz[fx] += sz[fy];
    }
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        m = 0, init(), mp.clear();
        for (int k = 1; k <= n; k++) {
            cin >> i[k] >> j[k] >> e[k];
            int di = discrete(i[k]), dj = discrete(j[k]);
            if (e[k] == 1) {
                merge(di, dj);
            }
        }
        bool ok = true;
        for (int k = 1; k <= n; k++) {
            int di = mp[i[k]], dj = mp[j[k]];
            if (e[k] == 0 && get(di) == get(dj)) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "YES" : "NO") << endl;
    }
    return 0;
}