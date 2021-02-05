/*
注意负半轴方向也是无限延伸的

相比题目 172，所有区域都是硬地，对应的也将数据范围增加到了 10^9
因此距离数组应该使用 map 来存储

反过来算，目标终点为 (x, y)
从起点 (0, 0) 出发，可以到达的点有：
(3, 0)
(0, 3)
...
(3k_1, 3k_2): 需要 (k_1 + k_2) 步，并且一定是最小的步数

首先从 (0, 0) 到 (x/3*3, y/3*3)
然后从 (x/3*3, y/3*3) 到 (x, y) 利用 BFS 进行计算即可

(0, 0) -> (3, 1) 的最佳方案不一定包括 (0, 0) -> (3, 0)（有更优的方案）
但是 (0, 0) -> (6, 1) 的方案一定包含 (0, 0) -> (3, 0)
因此首先看 x/6 ，表示可以走多少次 (0, 0) -> (3, 0)，然后剩下的部分运行自然的 BFS 即可。

可以看看抽风大佬的代码，实际上经过这么一个类似等差数列的递推公式计算之后，BFS的部分横纵坐标实际上很小了，不会超过 200，所以直接 prework 一遍算出 (0, 0) 到 (200, 200) 以内所有点的转移代价，然后后续直接使用也是可以的。
*/
#include <cassert>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

string s, t[] = {"U", "V", "H"};
int x, y, ans;
struct rec {
    // lie = 0 表示长方体立在 (x, y)
    // lie = 1 表示长方体横着躺着，左半部分位置在 (x, y)
    // lie = 2 表示长方体竖着躺着，上半部分位置在 (x, y)
    int x, y, lie;
    const bool operator==(const rec &b) const {
        return x == b.x && y == b.y && lie == b.lie;
    }
};
rec st, ed;
// 3 个不同 lie 情况（0, 1, 2，立, 横, 竖）下，朝上、右、下、左滚动后的坐标变化
const int next_x[3][4] = {
    {-2, 0, 1, 0},
    {-1, 0, 1, 0},
    {-1, 0, 2, 0}};
const int next_y[3][4] = {
    {0, 1, 0, -2},
    {0, 2, 0, -1},
    {0, 1, 0, -1}};
const int next_lie[3][4] = {
    {2, 1, 2, 1},
    {1, 0, 1, 0},
    {0, 2, 0, 2}};
int bfs() {
    // 因为一定是在 3*3 之内的拓展，实际上可以直接分情况讨论
    // 这里还是运行一遍 BFS
    unordered_map<int, unordered_map<int, unordered_map<int, int>>> d;
    queue<rec> q;
    d[st.x][st.y][st.lie] = 0;
    // 特殊情况
    if (st == ed) return 0;
    q.push(st);
    while (q.size()) {
        rec now = q.front();
        q.pop();
        // cout << now.x << " " << now.y << " " << now.lie << endl;

        // 4 个方向滚动
        for (int i = 0; i < 4; i++) {
            rec next;
            next.x = now.x + next_x[now.lie][i];
            next.y = now.y + next_y[now.lie][i];
            next.lie = next_lie[now.lie][i];
            // 方向都走错了的话，没有必要拓展了
            if (next.x > st.x && next.y < st.y) continue;

            if (!d[next.x][next.y].count(next.lie)) {
                d[next.x][next.y][next.lie] =
                    d[now.x][now.y][now.lie] + 1;
                // cout << next.x << " " << next.y << " " << next.lie << " " << d[now.x][now.y][now.lie] << endl;
                q.push(next);
                // 到达目标，广搜按照入队的选后顺序有层次单调性，第一次被入队时，就得到了从起始状态到达该状态的最少步数
                if (next.x == ed.x && next.y == ed.y && next.lie == ed.lie) return d[next.x][next.y][next.lie];
            }
        }
    }
    // 无解
    assert(false);
    return -1;
}
int M = 2;
int main() {
    while (cin >> s >> x >> y) {
        ans = 0;
        int k1 = (x - 3) / 3 / M, k2 = (y - 3) / 3 / M;
        k1 = max(k1, 0), k2 = max(k2, 0);
        ans += (k1 + k2) * 2 * M;

        // 因为 172 用的是数组坐标，这题用的是坐标系坐标
        // y 是行方向，x 是列方向，这里变换一下和 172 题目对应
        st = {-k2 * 3 * M, k1 * 3 * M, 0};
        ed = {-y, x, 0};
        for (int i = 0; i < 3; i++) {
            if (s == t[i]) {
                ed.lie = i;
                if (i == 2)
                    ed.x--;
                break;
            }
        }
        // cout << "Goal: " << ed.x << " " << ed.y << " " << ed.lie << endl;
        ans += bfs();

        cout << ans << endl;
    }
}