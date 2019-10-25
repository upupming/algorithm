#include <iostream>
#include <queue>
#include <iomanip>
#include <assert.h>

using namespace std;

int n, m, k, q, t[1010], qi, doneT[1010];
// serving[i] 表示窗口 i 正在服务的人数（inside the yellow line）
queue<int> serving[25];
bool sorry[1010];

void solve() {
    for (int i = 1; i <= k; i++) {
        int minQueueLen = m, minQueueIndex = -1;
        for (int j = 0; j < n; j++) {
            if (serving[j].size() < minQueueLen) {
                minQueueLen = serving[j].size();
                minQueueIndex = j;
            }
        }
        // 如果有【没有占满的窗口】，就上前去
        if (minQueueIndex != -1) {
            if (serving[minQueueIndex].empty()) doneT[i] = 8 * 60 + t[i];
            else {
                int start = doneT[serving[minQueueIndex].back()];
                // 注意是开始时间必须严格小于 17 * 60，注意不能直接将 doneT[i] 置为 -1，否则会对后面的计算造成影响，因此另开一个 bool 数组
                if (start >= 17 * 60) sorry[i] = true;
                doneT[i] = start + t[i];
            }
            // cout << i << ", " << doneT[i] << endl;
            serving[minQueueIndex].push(i);
        } else {
        // 如果所有窗口已满，取出最早出队伍的那个
            int minW = -1, minT = 99999999;
            for (int s = 0; s < n; s++) {
                // 从左到右遍历，要求必须严格 < 才替换
                // If there are two or more lines with the same length, the customer will always choose the window with the smallest number.
                if (doneT[serving[s].front()] < minT) {
                    minW = s;
                    minT = doneT[serving[s].front()];
                }
            };
            assert(minW != -1);
            int start = doneT[serving[minW].back()];
            if (start >= 17 * 60) sorry[i] = true;
            doneT[i] = start + t[i];
            serving[minW].pop();
            serving[minW].push(i);
        }
    }
}

int main() {
    cin >> n >> m >> k >> q;
    for (int i = 1; i <= k; i++) cin >> t[i];
    solve();
    while (q--) {
        cin >> qi;
        if (sorry[qi]) cout << "Sorry" << endl;
        else cout << setfill('0') << setw(2) << doneT[qi]/60 << ":" << setw(2) << doneT[qi]%60 << endl;
    }
    return 0;
}

/**
2 1 7 5
10000 200000 6 4 3 535 2
3 4 5 6 7

*/