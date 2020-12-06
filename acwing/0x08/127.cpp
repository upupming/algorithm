/*
贪心
注意 500 * x + 2 * y
因为 y <= 100, 2 * 100 < 500，所以 x 是优先于 y 考虑的
跟防晒的思路一样，先把任务按 x 降序排列（x 相同按 y 降序排列），然后每个任务选择最小的满足条件的机器。
*/
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int n, m;
pair<int, int> tasks[100010], machines[100010];
int main() {
    while (cin >> n >> m) {
        for (int i = 0; i < n; i++)
            cin >> machines[i].first >> machines[i].second;
        for (int i = 0; i < m; i++)
            cin >> tasks[i].first >> tasks[i].second;

        sort(machines, machines + n);
        sort(tasks, tasks + m);

        long long t = 0, ans = 0;
        multiset<int> ys;
        for (int i = m - 1, j = n - 1; i >= 0; i--) {
            int x = tasks[i].first, y = tasks[i].second;
            while (j >= 0 && machines[j].first >= x) {
                ys.insert(machines[j--].second);
            }
            auto it = ys.lower_bound(y);
            if (it != ys.end()) {
                t++;
                ans += 500 * x + 2 * y;
                ys.erase(it);
            }
        }
        cout << t << " " << ans << endl;
    }
    return 0;
}