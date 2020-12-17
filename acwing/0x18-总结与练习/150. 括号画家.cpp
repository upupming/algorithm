/*
用一个栈来模拟
把所有配对的括号删掉
遍历的时候求出来被删掉的连续一段的长度最大是多少 by yxc
*/
#include <iostream>
#include <stack>
using namespace std;

char b[2][4] = {"({[", ")}]"};
string s;
stack<int> stk;
int isClose(char ch) {
    for (int i = 0; i < 3; i++) {
        if (ch == b[1][i]) return i;
    }
    return -1;
}
int main() {
    cin >> s;
    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
        auto close = isClose(s[i]);
        // 匹配不到左括号的话
        if (stk.empty() || close == -1 || (close != -1 && s[stk.top()] != b[0][close])) stk.push(i);
        // 匹配到的话
        else
            stk.pop();

        // 此时满足题意的连续的那一段就是 (栈顶, i]
        if (stk.size())
            ans = max(ans, i - stk.top());
        else
            ans = max(ans, i + 1);
    }
    cout << ans << endl;
    return 0;
}