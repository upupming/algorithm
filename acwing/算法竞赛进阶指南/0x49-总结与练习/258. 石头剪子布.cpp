/*
布 > 石头
石头 > 剪刀
剪刀 > 布
这道题和「食物链」是差不多的，每个小朋友 x 可以被分为 x_enemy, x_self, x_eat 三个域
算法：
枚举第 i 个小朋友为裁判，如果发现矛盾的情况：
1. 矛盾者之一是第 i 个小朋友，忽略，因为第 i 个小朋友想出啥就出啥，没有问题
2. 否则，说明第 i 个小朋友不是裁判

- 如果可能的裁判数 >= 2，那么就是 Can not determine
- 如果可能的裁判数 == 1，那么就是确定的，记录一下确定的轮次（这个轮次是其他所有人当裁判发现的不能满足的行的最大值）；特殊情况，0 条记录的时候直接返回 0 即可，参考最后一个样例
- 如果可能的裁判数 == 0，那就是 impossible

时间复杂度 O(N^2)
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 3 * 510, M = 2010;

int n, m;
int fa[N], sz[N], d[N];
// line[i] 表示记录一下以第 i 个人为裁判的话，会在第几行发现不合法
// 用于计算
int line[N];
void init() {
    // 初始化，注意这个题目的节点编号从 0 开始
    for (int i = 0; i <= N; i++) {
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

char op[M];
int x[M], y[M];
int main() {
    while (cin >> n >> m) {
        for (int k = 1; k <= m; k++) {
            cin >> x[k] >> op[k] >> y[k];
            // 不妨设 x >= y
            if (op[k] == '<') swap(x[k], y[k]);
        }
        int cnt = 0, ans_p, ans_l = 0;
        memset(line, 0, sizeof line);
        // 枚举第 i 个小朋友为裁判
        for (int i = 0; i < n; i++) {
            init();
            bool ok = true;
            for (int k = 1; k <= m; k++) {
                // cout << i << ", " << k << endl;
                int x_self = x[k], x_eat = x[k] + n, x_enemy = x[k] + 2 * n;
                int y_self = y[k], y_eat = y[k] + n, y_enemy = y[k] + 2 * n;
                // cout << x_self << " " << y_self << endl;
                // cout << get(x_self) << " " << get(x_eat) << " " << get(x_enemy) << endl;
                // cout << get(y_self) << " " << get(y_eat) << " " << get(y_enemy) << endl;

                // 如果两个人出的手势是一样的
                if (op[k] == '=') {
                    // 判断是否有矛盾
                    if (
                        // x > y
                        get(x_eat) == get(y_self) ||
                        // x < y
                        get(x_enemy) == get(y_self)) {
                        // 不能满足，直接换个裁判
                        ok = false;
                        line[i] = k;
                        break;

                    }
                    // 没有矛盾的话，合并 3 个域
                    else {
                        // 如果是裁判，不加入并查集
                        if (x_self == i || y_self == i) continue;
                        merge(x_self, y_self);
                        merge(x_eat, y_eat);
                        merge(x_enemy, y_enemy);
                    }
                } else
                // x > y
                {
                    if (
                        // x 与 y 是相同的
                        get(x_self) == get(y_self) ||
                        // y > x
                        get(y_eat) == get(x_self)) {
                        // 不能满足，直接换个裁判
                        ok = false;
                        line[i] = k;
                        break;
                    } else {
                        // 如果是裁判，不加入并查集
                        if (x_self == i || y_self == i) continue;
                        // 1. x 的同类域 == y 的天敌域
                        merge(x_self, y_enemy);
                        // 2. x 的捕食域 == y 的同类域
                        merge(x_eat, y_self);
                        // 3. 根据环形关系，x 的天敌域 == y 的捕食域
                        merge(x_enemy, y_eat);
                    }
                }
            }
            cnt += ok;
            if (ok) ans_p = i;
        }
        if (cnt == 0)
            cout << "Impossible" << endl;
        else if (cnt == 1) {
            for (int i = 0; i < n; i++) {
                ans_l = max(ans_l, line[i]);
            }
            cout << "Player " << ans_p << " can be determined to be the judge after " << ans_l << " lines" << endl;
        } else
            cout << "Can not determine" << endl;
    }
    return 0;
}