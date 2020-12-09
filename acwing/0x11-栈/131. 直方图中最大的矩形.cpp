/*
考虑每个矩形作为最低点的情况，右边一旦出现比他高度小的矩形，他可以延伸的足以大宽度就确定了。
维护一个单调栈，每次入栈前，判断栈顶元素和入栈元素大小，如果栈顶元素较大，需要出栈并计算其最大面积。入栈的时候的宽度代表当前矩形可以向左延伸的最大宽度。
*/
#include <iostream>
#include <stack>
using namespace std;

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