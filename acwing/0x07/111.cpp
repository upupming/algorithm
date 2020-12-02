/*
牛应该按照开始时间进行排序。如果解是大于 m，必然存在 m+1 个区间存在交集的，解至少是 m+1。
*/
#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
using namespace std;

typedef pair<int, int> PII;
// s 记录第 i 个畜栏的最后一头牛的编号
int n, ans[50050], visited[50050], cnt;
// <<牛起始时间, 牛终止时间>, 牛编号 (0-indexed)>
pair<PII, int> c[50050];
// 必须用堆，否则 TLE
// <畜栏最后一头牛的吃草结束时间, 畜栏编号>
priority_queue<PII, vector<PII>, greater<PII>> pq;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> c[i].first.first >> c[i].first.second, c[i].second = i;
    sort(c, c + n);

    for (int i = 0, j = 1; i < n; i++) {
        // 能安排进畜栏
        if (!pq.empty() && c[i].first.first > pq.top().first) {
            PII p = pq.top();
            pq.pop();
            pq.push(make_pair(c[i].first.second, p.second));
            ans[c[i].second] = p.second;
        } else {
            // 不能安排进畜栏，新建一个
            ans[c[i].second] = j;
            pq.push(make_pair(c[i].first.second, j++));
        }
    }

    cout << pq.size() << endl;
    for (int i = 0; i < n; i++) cout << ans[i] << endl;
    return 0;
}