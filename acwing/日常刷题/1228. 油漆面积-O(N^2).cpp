/*
扫描线算法
大家一般习惯用竖直方向的线来做扫描线，从左向右依次扫描
其实也可以用水平方向的线来扫描，这只是一个习惯问题

首先将所有的矩形分为左竖边（入边）和右竖边（出边），分别用 1 和 -1 表示
在扫描的过程中，维护一个 y 左边上的区间 ySection = [minY, maxY] 表示当前需要算入面积的竖直方向区间，同时区间上每个 y 值都要维护一个次数，表示入边覆盖次数减去出边覆盖次数，不妨记为 c 数组
每次扫描线向右移动：
- 计算面积 = ySection 长度 * x 移动的距离
- 如果遇到入边，所有入边上的 y 坐标 c 值都 +1
- 如果遇到出边，所有入边上的 y 坐标 c 值都 -1

实际计算 c 的过程中，c[i] 表示的是第 i 个 y 方向上的区间，所有可能的 y 方向上的区间是经过排序之后从小到大生成的

时间复杂度为 O(N^2)，显然会 TLE，因此需要用线段树进行优化
*/
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1e4 + 10;

struct Segment {
    int x, y1, y2;
    int k;
    bool operator<(const Segment& b) {
        return x < b.x;
    }
} seg[N * 2];

int n, x1, x2, y1, y2;
int c[N * 2], y[N * 2];
int main() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        // 左边为入边，k = 1
        seg[2 * i - 1].x = x1, seg[2 * i - 1].y1 = y1, seg[2 * i - 1].y2 = y2, seg[2 * i - 1].k = 1;
        // 右边为出边，k = -1
        seg[2 * i].x = x2, seg[2 * i].y1 = y1, seg[2 * i].y2 = y2, seg[2 * i].k = -1;
        // 存储所有的 y 坐标
        y[2 * i - 1] = y1;
        y[2 * i] = y2;
    }
    // 出入边均按照 x 坐标从小到大排序
    sort(seg + 1, seg + 1 + 2 * n);
    // 把 y 方向的区间进行排序
    sort(y + 1, y + 1 + 2 * n);
    int ans = 0;
    for (int i = 1; i <= 2 * n; i++) {
        // 计算扫描线在竖直方向上的长度
        int len = 0;
        for (int j = 1; j < 2 * n; j++) {
            // 如果这个区间被覆盖次数 >=1，长度就要统计上
            if (c[j]) len += y[j + 1] - y[j];
        }
        if (i >= 2)
            ans += len * (seg[i].x - seg[i - 1].x);
        // 更新 c 数组
        for (int j = 1; j < 2 * n; j++) {
            if (seg[i].y1 <= y[j] && seg[i].y2 >= y[j + 1])
                c[j] += seg[i].k;
        }
        // cout << i << " " << len << " " << seg[i].x << " " << seg[i - 1].x << " " << ans << endl;
    }
    cout << ans << endl;
    return 0;
}
