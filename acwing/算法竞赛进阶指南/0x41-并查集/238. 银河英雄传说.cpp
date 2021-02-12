/*
「边带权」并查集
d[x] 表示从 x 到树根的路径上所有边权之和，递推关系 d[x] = d[f[x]] + weight(f[x], x)
对于指令：
M x y: 把 x 的树根作为 y 的树根的子节点，连接的新边的权值应该设为合并之前集合 y 的大小，因为集合 y 中的全部战舰都排在集合 x 之前
*/
#include <iostream>
using namespace std;
const int N = 3e4 + 10;

// sz 表示节点的秩，这里定义为节点的元素个数
int fa[N], sz[N], d[N];
void init() {
    // 初始化
    for (int i = 1; i <= N; i++) {
        fa[i] = i;
        sz[i] = 1;
    }
}
// Get 操作，时间复杂度为反阿克曼函数，可以认为是常数
int get(int x) {
    if (x == fa[x]) return x;
    // 递归计算 d[fa[x]]
    int root = get(fa[x]);
    // 再更新 d[x]
    d[x] += d[fa[x]];
    // 路径压缩，fa 直接赋值为代表元素
    return fa[x] = root;
}
// Merge 操作，同上，可以认为时间复杂度为常数
// 规定 x 放在 y 的后面
void merge(int x, int y) {
    int fx = get(x), fy = get(y);
    if (fx == fy) return;

    fa[fx] = fy;
    // fx 到 fy 一共有 sz[fy] 个战舰
    d[fx] = sz[fy];
    sz[fy] += sz[fx];
}

int t, i, j;
string s;
int main() {
    init();
    cin >> t;
    while (t--) {
        cin >> s >> i >> j;
        if (s[0] == 'M')
            merge(i, j);
        else {
            // cout << d[i] << " " << d[j] << endl;
            if (get(i) == get(j)) {
                // cout << d[i] << " " << d[j] << endl;
                cout << abs(d[i] - d[j]) - 1 << endl;
            } else
                cout << -1 << endl;
        }
    }
    return 0;
}