/*
考虑每个矩形作为最低点的情况，右边一旦出现比他高度小的矩形，他可以延伸的足以大宽度就确定了。
维护一个单调栈，每次入栈前，判断栈顶元素和入栈元素大小，如果栈顶元素较大，需要出栈并计算其最大面积。入栈的时候的宽度代表当前矩形可以向左延伸的最大宽度。

还可以用单调栈先生成数组 left[i]、right[i] 表示矩形 i 在左边、右边第一个小于矩形 i 的高度的下标，每个矩形的最大延伸面积就是 h[i] * (right[i] - left[i] + 1)
*/
#include <algorithm>
#include <iostream>
#include <stack>
using namespace std;

// y 总的计算 left 和 right 数组的方法
int n, h[100010], lft[100010], rht[100010], stk[100010];

void get(int *left) {
    // 这里设置哨兵为 -1，使得第一个元素可以直接 push
    h[0] = -1;
    // 当前栈顶指针
    int p = 0;
    for (int i = 1; i <= n; i++) {
        while (h[stk[p]] >= h[i]) p--;
        left[i] = stk[p];
        stk[++p] = i;

        // cout << i << " " << left[i] << endl;
    }
}
int main() {
    while (cin >> n && n != 0) {
        // 这里 i 从 1 开始是为了方便在 0 处放一个哨兵
        for (int i = 1; i <= n; i++) cin >> h[i];
        get(lft);
        reverse(h + 1, h + 1 + n);
        get(rht);

        long long ans = 0;
        for (int i = 1, j = n; i <= n; i++, j--) {
            auto width = (i - lft[i]) + (j - rht[j]) - 1ll;
            // cout << i << " " << h[j] << " " << width << endl;
            ans = max(ans,
                      // 宽度 * 高度
                      //   因为 h 被 reverse 过了，一定要记得这里用 h[j] 而不是 h[i]
                      width * h[j]);
        }
        cout << ans << endl;
    }

    return 0;
}

/*
书上的动态调整宽度的方法

int n, x;
stack<int> h, w;
int main() {
    while (cin >> n && n != 0) {
        long long ans = 0;
        h = stack<int>();
        for (int i = 0; i < n; i++) {
            cin >> x;
            int width = 0;
            while (!h.empty() && h.top() > x) {
                // 累加作为右侧可以到达的最远距离
                width += w.top();
                ans = max(ans, (long long)h.top() * width);
                h.pop(), w.pop();
            }
            // 这里 w 的值一定要想清楚，如果前面有更高的被 pop 出来，实际上向左可以延伸的宽度是这些的总宽度 + 1
            h.push(x), w.push(width + 1);
        }
        int width = 0;
        // 最后把栈里面的元素清空
        while (!h.empty()) {
            width += w.top();
            ans = max(ans, (long long)h.top() * width);
            h.pop(), w.pop();
        }
        cout << ans << endl;
    }
    return 0;
}
*/