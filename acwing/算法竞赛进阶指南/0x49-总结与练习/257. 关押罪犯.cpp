/*
采用扩展域的并查集算法，每个罪犯 x 分成两个状态，一个是 x1 表示 x 在监狱 1 里面，一个是 x2 表示 x 在监狱 2 里面。

贪心：从大到小考虑每一个冲突关系
每个冲突关系 x, y 意味着：
- x1 与 y2 在同一个集合里面
- x2 与 y1 在同一个集合里面
如果与之前矛盾，那么说明 x 和 y 只能安排在一起，输出当前的冲突值即可、
*/
#include <algorithm>
#include <iostream>
using namespace std;
// 因为有两个域，N 需要乘以 2
const int N = 2 * 2e4 + 10, M = 1e5 + 10;

int n, m;
struct P {
    int x, y, c;
    bool operator<(const P &b) {
        return c > b.c;
    }
} p[M];

int fa[N], sz[N], d[N];
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

int main() {
    cin >> n >> m;
    init();
    for (int i = 1; i <= m; i++) {
        cin >> p[i].x >> p[i].y >> p[i].c;
    }
    sort(p + 1, p + m + 1);
    for (int i = 1; i <= m; i++) {
        int x1 = p[i].x, x2 = x1 + n;
        int y1 = p[i].y, y2 = y1 + n;
        int fx1 = get(x1), fy1 = get(y1);
        int fx2 = get(x2), fy2 = get(y2);
        // 如果之前的条件要求必须同时在监狱 1 里面，这个冲突必定会产生
        if (fx1 == fy1) {
            cout << p[i].c << endl;
            return 0;
        } else {
            // 为了不产生冲突，两个罪犯必须在不同的监狱
            fa[fx1] = fy2;
            fa[fx2] = fy1;
        }
    }
    // 不会产生冲突
    cout << 0 << endl;
    return 0;
}