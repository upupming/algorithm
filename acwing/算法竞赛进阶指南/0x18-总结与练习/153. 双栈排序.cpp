/*
一旦确定了每个数属于哪一个栈，那么入栈顺序就确定了，出栈顺序也确定了。
对于每对 i, j，如果存在 k，i < j < k 且 a[k] < a[i] < a[j]，那么 i 和 j 一定不能放在同一个栈里面。
2 3 1
枚举所有 i 和 j，如果 i 满足上述条件，就连一条边，问题就转化成了利用染色法判断这个图是不是二分图，如果是二分图，那么序列就是合法的。
为了方便地求 k，求一下后缀最小值 f[i] 表示从 a[i] - a[n] 的最小值。

染色染好之后就确定了每个数该入哪一个栈，在入栈的过程中有一些策略来使得字典序最小（参见代码注释）

https://www.acwing.com/solution/acwing/content/3710/
染色法：《算法竞赛进阶指南》第 423 页
*/
#include <algorithm>
#include <cstring>
#include <iostream>
#include <stack>
using namespace std;
const int N = 1010;

int n;
int a[N], f[N];
int color[N];
// i 和 j 的邻接矩阵
bool g[N][N];

bool dfs(int x, int c) {
    color[x] = c;
    for (int i = 1; i <= n; i++) {
        if (g[x][i]) {
            if (color[i] == c) return false;
            if (color[i] == 0 && !dfs(i, 3 - c)) return false;
        }
    }
    return true;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    // 因为输入范围是 1 ~ n，这里最大值用 n + 1 即可
    f[n + 1] = n + 1;
    for (int i = n; i >= 1; i--) f[i] = min(f[i + 1], a[i]);

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (a[i] < a[j] && f[j + 1] < a[i]) {
                g[i][j] = g[j][i] = 1;
            }
        }
    }

    bool flag = 1;
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0 && !dfs(i, 1)) {
            flag = 0;
            break;
        }
    }
    if (!flag) {
        cout << 0 << endl;
        return 0;
    }

    stack<int> stk1, stk2;
    int now = 1;
    // 对每个数进行进栈操作
    for (int i = 1; i <= n; i++) {
        if (color[i] == 1) {
            // 要入第一个栈了，第一个栈该出的现在必须要出掉
            // 为了使字典序最小，第二个栈可以再等等
            while (stk1.size() && stk1.top() == now) {
                stk1.pop();
                cout << "b ";
                now++;
            }
            stk1.push(a[i]);
            cout << "a ";
        } else {
            // 要入第二个栈了，第二个栈该出的现在必须要出掉
            // 然而由于 b 比 c 字典序小，第一个栈可以出的也应该出掉
            while (true) {
                if (stk1.size() && stk1.top() == now) {
                    stk1.pop();
                    cout << "b ";
                    now++;
                } else if (stk2.size() && stk2.top() == now) {
                    stk2.pop();
                    cout << "d ";
                    now++;
                } else
                    break;
            }
            stk2.push(a[i]);
            cout << "c ";
        }
    }
    // 最后出栈剩余的
    while (true) {
        if (stk1.size() && stk1.top() == now) {
            stk1.pop();
            cout << "b ";
            now++;
        } else if (stk2.size() && stk2.top() == now) {
            stk2.pop();
            cout << "d ";
            now++;
        } else
            break;
    }
    cout << endl;
    return 0;
}