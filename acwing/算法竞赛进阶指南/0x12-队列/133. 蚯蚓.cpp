/*
优先队列，模拟一遍即可
难点在于：此外，除了刚刚产生的两只新蚯蚓，其余蚯蚓的长度都会增加一个非负整数 q 。可以采用逆向思维，用一个 add 变量累积总共需要加的数，然后这两个新蚯蚓的长度减去 add 再 push 即可。

书上还有一个优化，就是 floor(p * x) 和 x - floor(p * x) 这两个变量按照时间一定是严格递减的，所以可以用队列维护，不需要用优先队列。
*/
#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
using namespace std;

int n, m, q, u, v, t, x, cnt, add, a[100010];
double p;
queue<int> q1, q2, q3;
int top() {
    int x = 0x80000000;
    if (!q1.empty() && q1.front() > x) x = q1.front();
    if (!q2.empty() && q2.front() > x) x = q2.front();
    if (!q3.empty() && q3.front() > x) x = q3.front();
    return x;
}
bool empty() { return q1.empty() && q2.empty() && q3.empty(); }
void pop() {
    queue<int>* q = nullptr;
    // 队列里面的最小值不是 0，因为都是减去过 add 的
    int x = 0x80000000;
    if (!q1.empty() && q1.front() > x) x = q1.front(), q = &q1;
    if (!q2.empty() && q2.front() > x) x = q2.front(), q = &q2;
    if (!q3.empty() && q3.front() > x) x = q3.front(), q = &q3;
    // cout << x<< " " <<q << endl;
    if (q && !q->empty())
        q->pop();
}
int main() {
    cin >> n >> m >> q >> u >> v >> t;
    p = double(u) / v;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    for (int i = n - 1; i >= 0; i--) {
        q1.push(a[i]);
    }
    for (int i = 1; i <= m; i++) {
        x = top() + add, pop();
        if (i % t == 0) {
            if (cnt++ > 0) cout << " ";
            cout << x;
        }
        add += q;
        q2.push(floor(p * x) - add);
        q3.push(x - floor(p * x) - add);
        // cout << endl
        //      << i << " " << floor(p * x) - q << " " << x - floor(p * x) - q << endl;
    }
    cout << endl;
    cnt = 0;
    bool space = false;
    while (!empty()) {
        x = top() + add, pop();
        if (++cnt % t == 0) {
            if (space) cout << " ";
            cout << x, space = true;
        }
    }
    cout << endl;
    return 0;
}