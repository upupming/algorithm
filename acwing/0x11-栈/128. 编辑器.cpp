/*
问题的关键就是维护当前光标左侧的 max S_i 信息，S_i 就是前缀和
如何在 O(1) 时间复杂度内获得 S_1, ..., S_k 中的最大值？
跟上一题一样维护一个 T 数组，T_k = max{S_1, ..., S_k} 即可
每次移动光标，增删元素都需要更新 S 和 T 数组，只需要 O(1) 时间即可完成
这样做的缺点是删除/增加的时候不太好处理，需要对数组进行移动，需要 O(n) 的时间。还是会 TLE

正确的做法是「对顶栈」，增删在 A 的栈顶执行，移动则在 A,B 之间进行即可
*/

#include <cstring>
#include <iostream>
#include <stack>
using namespace std;

int q, s[1000010], t[1000010];
stack<int> a, b;
int main() {
    cin >> q;
    string cmd;
    memset(t, 0xf0, sizeof(t));
    int x;
    while (q--) {
        cin >> cmd;
        if (cmd == "I") {
            cin >> x;
            a.push(x);
            s[a.size()] = s[a.size() - 1] + x;
            t[a.size()] = max(t[a.size() - 1], s[a.size()]);
        } else if (cmd == "Q") {
            cin >> x;
            cout << t[x] << endl;
        } else if (cmd == "D") {
            if (!a.empty()) a.pop();
        } else if (cmd == "L") {
            if (!a.empty()) {
                x = a.top(), a.pop();
                b.push(x);
            }
        } else if (cmd == "R") {
            if (!b.empty()) {
                x = b.top(), b.pop();
                a.push(x);
                s[a.size()] = s[a.size() - 1] + x;
                t[a.size()] = max(t[a.size() - 1], s[a.size()]);
            }
        }
    }
    return 0;
}

/* 增删 O(n)，TLE
// cursor 表示光标位置，n 表示数组总大小
int q, cursor = 1, a[1000010], s[1000010], t[1000010], n, del;
int main() {
    cin >> q;
    string cmd;
    int x;
    memset(t, 0xf0, sizeof(t));
    while (q--) {
        cin >> cmd;
        if (cmd == "I") {
            for (int i = n; i >= cursor; i--) {
                a[i + 1] = a[i];
            }
            cin >> a[cursor];
            s[cursor] = a[cursor] + s[cursor - 1];
            t[cursor] = max(t[cursor - 1], s[cursor]);
            n++, cursor++;
        } else if (cmd == "Q") {
            cin >> x;
            cout << t[x] << endl;
        } else if (cmd == "D") {
            if (cursor >= 2) {
                cursor--, n--;
                for (int i = cursor; i <= n; i++) {
                    a[i] = a[i + 1];
                }
                s[cursor] = a[cursor] + s[cursor - 1];
                t[cursor] = max(t[cursor - 1], s[cursor]);
            }
        } else if (cmd == "L") {
            if (cursor >= 2)
                cursor--;
            // cout << "L " << cursor << endl;
        } else if (cmd == "R") {
            if (cursor <= n) {
                s[cursor] = a[cursor] + s[cursor - 1];
                t[cursor] = max(t[cursor - 1], s[cursor]);
                cursor++;
            }
        }
    }
    return 0;
}
*/