/*
跟数据备份是等价的，直接用数据备份的方法做即可
需要多加一个与处理过程，删掉 0 元素，将所有连续正段累加、所有连续负段累加（因为连续的正数和负数一定一起选）
先将所有正段全部选上，如果正数段数小于M直接输出
然后用最小堆维护需要删除的段，删除堆顶的 cnt - m 个即可

要想减少段数有两种方式：
1.删除一段正数
2.将多段正数和连接他们的负数一起选上
第一种选法直接将res-=这个值
第二种则相当于减去其中负数段的绝对值（画图考虑）；
进而将连续的负数记为绝对值
*/
#include <iostream>
#include <queue>
using namespace std;
const int N = 1e5 + 10;
typedef pair<int, int> PII;

int n, m;
int a[N], l[N], r[N];
// true 表示从 heap 中删除了
bool st[N];
void remove(int p) {
    r[l[p]] = r[p];
    l[r[p]] = l[p];
    st[p] = true;
}
int main() {
    cin >> n >> m;

    int k = 1;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if ((long long)a[k] * x < 0)
            a[++k] = x;
        else
            a[k] += x;
    }

    n = k;

    int cnt = 0, res = 0;
    // 先把所有的正数段选上
    for (int i = 1; i <= n; i++) {
        if (a[i] > 0) {
            cnt++;
            res += a[i];
        }
    }

    priority_queue<PII, vector<PII>, greater<PII>> heap;

    for (int i = 1; i <= n; i++) {
        l[i] = i - 1;
        r[i] = i + 1;
        heap.push({abs(a[i]), i});
    }

    while (cnt > m) {
        while (st[heap.top().second]) heap.pop();

        auto t = heap.top();
        heap.pop();

        int v = t.first, p = t.second;

        // 如果是负数并且在边界上，因为缺少一个正边界，最优方案不会选择这个负段进行合并，直接忽略
        if (l[p] != 0 && r[p] != n + 1 || a[p] > 0) {
            cnt--;
            res -= v;

            int left = l[p], right = r[p];
            // 正 - 负 - 负 = 三个相加
            // 当前决策表示删掉正段，push 的决策表示用两边的负段把这个正段连起来
            a[p] += a[left] + a[right];

            heap.push({abs(a[p]), p});
            remove(left);
            remove(right);
        }
    }

    cout << res << endl;

    return 0;
}