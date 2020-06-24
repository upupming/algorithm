#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int t;
long long bound = 1000000000;
string cmd;

long long mod(long long a, long long b) {
    long long ret = a % b;
    return ret >= 0 ? ret : ret + b;
}

void run(const char& c, long long& x, long long& y) {
    if (c == 'N') y = mod((y - 1), bound);
    if (c == 'S') y = mod((y + 1), bound);
    if (c == 'E') x = mod((x + 1), bound);
    if (c == 'W') x = mod((x - 1), bound);
}

pair<int, int> solve() {
    stack<char> moves;
    stack<long long> xs, ys;
    long long x = 0, y = 0;

    for (int i = 0; i < cmd.length(); i++) {
        if (cmd[i] == ')') {
            long long xx = xs.top(), yy = ys.top();
            xs.pop();
            ys.pop();

            while (moves.top() != '(') {
                // 执行当前括号内的所有命令，指令执行顺序不影响结果
                char c = moves.top();
                run(c, xx, yy);
                moves.pop();
            }
            // `(` 出栈
            moves.pop();
            // 倍数出栈
            int times = moves.top() - '0';
            moves.pop();

            if (!xs.empty()) {
                xs.top() = mod(xs.top() + xx * times, bound);
                ys.top() = mod(ys.top() + yy * times, bound);
            } else {
                x = mod(x + xx * times, bound);
                y = mod(y + yy * times, bound);
            }

        } else {
            if (cmd[i] == '(') {
                xs.push(0);
                ys.push(0);
            }
            moves.push(cmd[i]);
        }
    }

    while (!moves.empty()) {
        char c = moves.top();
        run(c, x, y);
        moves.pop();
    }

    return make_pair(x + 1, y + 1);
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> cmd;
        pair<int, int> ans = solve();
        printf("Case #%d: %d %d\n", i, ans.first, ans.second);
    }
    return 0;
}