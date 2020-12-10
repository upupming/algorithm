/*
维护 t 个队列，同时用 m[i] = j 表示第 i 类在第 j 个队列里面，o[j] = i

书上的做法：实际上是把 m 和 n 也当做一个队列来处理了，用一个存小组编号的队列维护当前的所有组，也能够实现按序的出队列。
*/

#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int t, m[1010], o[1010], cls[1000010], n, x, cnt, idx;
string cmd;
vector<queue<int>> qs;
int main() {
    while (cin >> t, t) {
        qs.clear();

        cout << "Scenario #" << (++cnt) << endl;
        memset(m, 0xff, sizeof(m));
        memset(o, 0xff, sizeof(o));
        idx = 0;
        for (int i = 0; i < t; i++) {
            cin >> n;
            for (int j = 0; j < n; j++) {
                cin >> x;
                cls[x] = i;
            }
        }
        while (cin >> cmd, cmd != "STOP") {
            if (cmd[0] == 'E') {
                cin >> x;
                if (m[cls[x]] == -1) {
                    // 创建一个新的队列
                    qs.push_back(queue<int>());
                    m[cls[x]] = qs.size() - 1;
                    o[qs.size() - 1] = cls[x];
                }
                // 加入到对应的队列
                qs[m[cls[x]]].push(x);
            } else if (cmd[0] == 'D') {
                cout << qs[idx].front() << endl;
                qs[idx].pop();
                if (qs[idx].empty()) m[o[idx]] = -1, o[idx] = -1, idx++;
            }
        }
        cout << endl;
    }
    return 0;
}