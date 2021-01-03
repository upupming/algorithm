/*
每个小岛的坐标 (x, y) 对应 x 轴上的一个雷达可以取的区间
区间为以 (x, y) 为圆心，d 为半径的圆与 x 轴的交线，如果没有交线，意味着这一点无论如何都不可能被检测到，直接输出 -1
贪心方案就是，区间选点来覆盖，将区间按照终止点排序，对于每个区间，选右端点作为雷达点，后面可以被容纳进的也都容纳进来，直到有开始点超出当前点，新建雷达即可。
正确性：假设上述构造的解为 S 个雷达，上述构造法一定有 S 个互不相交的区间，每个互不相交的区间至少得一个雷达，最优解 >= S，所以这是最优解
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
using namespace std;

int n, d;
// <终止点, 起始点>，因为要按照终止点排序，所以终止点放在前面
pair<double, double> c[1010];
int main() {
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        if (y > d) {
            cout << -1 << endl;
            return 0;
        }
        double m = sqrt(d * d - y * y);
        c[i].second = x - m;
        c[i].first = x + m;
    }
    sort(c, c + n);
    double cur = INT_MIN, ans = 0;
    for (int i = 0; i < n; i++) {
        if (c[i].second <= cur)
            continue;
        else {
            cur = c[i].first;
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}