/*
浮点运算，三位小数，所以 eps 用 10^-5
就是点集 A, B 中各拿一个点，使得距离最小

10^5 数据范围只能用 O(n log n) 的算法
对于 A 中每一个点 a，如何快速找出 B 中离 a 最近的点

先想一个经典的分治问题：不分类别的一堆点中最近的两点，直接每次用中间一条线二分分治即可，合并的时候，假设 delta = min(左子问题, 右子问题)，就只需要枚举左子问题的到边界线不超 delta 距离的点，以及右子问题的到边界线不超 delta 距离的点。计算距离的时候只需要计算 delta 半径内的点（进一步转换为宽 delta 高 2 * delta 的矩形区域），可以证明每个最多只有 6 个需要计算距离的点。

对于两类点的情况，也是很巧妙了，整体流程同上，但是不在同一类的点在计算距离的时候直接返回正无穷。但是特殊情况的数据会导致时间复杂度退化成 O(n^2)，但是数据比较水不考虑。

快速计算矩形区域的点需要对 y 进行排序，在归并的时候进行
*/

#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

const double inf = 1e10;
struct Point {
    int x, y, type;
    bool operator<(const Point& b) {
        return x < b.x;
    }
} point[200010], tmp[200010];
int n, t;
double dis(Point& a, Point& b) {
    // cout << (a.type == b.type) << endl;
    if (a.type == b.type) return inf;
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
double dfs(int l, int r) {
    if (l >= r) return inf;
    int mid = (l + r) >> 1;
    double delta = min(dfs(l, mid), dfs(mid + 1, r));

    // 子问题已经按照 y 排好序，归并一下
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (point[i].y <= point[j].y)
            tmp[k++] = point[i++];
        else
            tmp[k++] = point[j++];
    }
    while (i <= mid) tmp[k++] = point[i++];
    while (j <= r) tmp[k++] = point[j++];
    for (int i = l; i <= r; i++) point[i] = tmp[i];

    k = 0;
    // 找出位于 -delta 和 delta 之间的点
    for (int i = l; i <= r; i++) {
        if (abs(point[i].x - point[mid].x) < delta) {
            tmp[k++] = point[i];
        }
    }
    // y 已经排好序，按序组合，可提前中断，虽然是双重循环，但是是常数（每个点最多 6 对）时间
    for (int i = 0; i < k; i++) {
        // 如果超出 delta 可直接中断
        for (int j = i + 1; j < k && tmp[j].y - tmp[i].y < delta; j++) {
            // cout << tmp[i].x << ", " << tmp[i].y << "; "
            //      << tmp[j].x << ", " << tmp[j].y << "; "
            //      << dis(tmp[i], tmp[j]) << endl;
            delta = min(delta, dis(tmp[i], tmp[j]));
        }
    }

    return delta;
}
int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> point[i].x >> point[i].y;
            point[i].type = 0;
        }
        for (int i = n; i < 2 * n; i++) {
            cin >> point[i].x >> point[i].y;
            point[i].type = 1;
        }
        // 后续归并划分需要先按照 x 排序
        sort(point, point + 2 * n);

        printf("%.3lf\n", dfs(0, 2 * n - 1));
    }
    return 0;
}