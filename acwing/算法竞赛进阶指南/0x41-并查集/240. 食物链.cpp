/*
同样可用边带权和扩展域的解法
我们这里参考书上使用扩展域的解法

扩展域在判断是不是假话的时候，对于同一个判断条件是有很多写法的，不影响
例如：
get(x_self) == get(y_eat)
与
get(x_enemy) == get(y_self)
是等价的，因为在 merge 的时候，对各种关系是都会进行处理的

y 总讲的方法是边带权的：
只要是相互吃的关系，就加进并查集里面
x 到根节点的距离为 d[x]，那么：
- d[x] % 3 == 1 表示 x 吃根节点
- d[x] % 3 == 2 表示根节点吃 x
- d[x] % 3 == 0 表示 x 和根节点是同类
x 和 y 和根节点的关系确定，x 和 y 两者的关系就确定了
初始化 d[x] = 0 表示自己是自己的同类
*/
#include <iostream>
using namespace std;
const int N = 3 * 5e4 + 10;

int fa[N], sz[N], n, k, ans, d, x, y;
void init() {
    for (int i = 1; i <= 3 * n; i++) {
        fa[i] = i;
        sz[i] = 1;
    }
}
int get(int x) {
    if (x == fa[x])
        return x;
    return fa[x] = get(fa[x]);
}
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
    cin >> n >> k;
    init();
    for (int i = 1; i <= k; i++) {
        cin >> d >> x >> y;
        if (x > n || y > n) {
            ans++;
            continue;
        }

        // 同类域、捕食域、天敌域
        int x_self = x, x_eat = x + n, x_enemy = x + 2 * n;
        int y_self = y, y_eat = y + n, y_enemy = y + 2 * n;
        // x 和 y 是同类
        if (d == 1) {
            // 判断是否与之前的真话矛盾
            if (
                // x 吃 y
                get(x_eat) == get(y_self)
                // y 吃 x
                || get(x_self) == get(y_eat)) {
                ans++;
                continue;
            }

            // x 和 y 的三个域都应该进行合并
            merge(x_self, y_self);
            merge(x_eat, y_eat);
            merge(x_enemy, y_enemy);
        } else {
            // x 吃 y
            // 判断是否与之前的真话矛盾
            if (
                // x 与 y 是同类
                get(x_self) == get(y_self)
                // y 吃 x
                || get(x_enemy) == get(y)) {
                ans++;
                continue;
            }
            // 1. x 的同类域 == y 的天敌域
            merge(x_self, y_enemy);
            // 2. x 的捕食域 == y 的同类域
            merge(x_eat, y_self);
            // 3. 根据环形关系，x 的天敌域 == y 的捕食域
            merge(x_enemy, y_eat);
        }
    }
    cout << ans << endl;
    return 0;
}