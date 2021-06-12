#include <bits/stdc++.h>
using namespace std;
typedef array<int, 3> AI3;
// 优先级
int grade(char op) {
    switch (op) {
        case '(':
            return 1;
        case '&':
        case '|':
            return 2;
    }
    return 0;
}
class Solution {
   public:
    // 结果、变成 0 需要次数、变成 1 需要次数
    vector<AI3> nums;
    vector<char> ops;
    void calc(char op) {
        // 从栈顶取出两个数
        auto y = nums.back();
        nums.pop_back();
        auto x = nums.back();
        nums.pop_back();
        int z, a0, a1;
        switch (op) {
            case '&':
                z = x[0] & y[0];
                if (x[0] == 0 && y[0] == 0) {
                    a0 = 0;
                    a1 = min(x[2] + 1, y[2] + 1);
                }
                if (x[0] == 0 && y[0] == 1) {
                    a0 = 0;
                    a1 = 1;
                }
                if (x[0] == 1 && y[0] == 0) {
                    a0 = 0;
                    a1 = 1;
                }
                if (x[0] == 1 && y[0] == 1) {
                    a0 = min(x[1], y[1]);
                    a1 = 0;
                }
                break;
            case '|':
                z = x[0] | y[0];
                if (x[0] == 0 && y[0] == 0) {
                    a0 = 0;
                    a1 = min(x[2], y[2]);
                }
                if (x[0] == 0 && y[0] == 1) {
                    a0 = 1;
                    a1 = 0;
                }
                if (x[0] == 1 && y[0] == 0) {
                    a0 = 1;
                    a1 = 0;
                }
                if (x[0] == 1 && y[0] == 1) {
                    a0 = min(x[1] + 1, y[1] + 1);
                    a1 = 0;
                }
                break;
        }
        nums.push_back({z, a0, a1});
    }
    int minOperationsToFlip(string s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '0') {
                nums.push_back({0, 0, 1});
            } else if (s[i] == '1') {
                nums.push_back({1, 1, 0});
            } else if (s[i] == '(') {
                ops.push_back('(');
            } else if (s[i] == ')') {
                while (ops.size() && ops.back() != '(') {
                    // 出栈一个符号就计算一下
                    char op = ops.back();
                    ops.pop_back();
                    calc(op);
                }
                // 左括号出栈（如果有的话）
                if (ops.size()) ops.pop_back();
            } else {
                while (ops.size() && grade(ops.back()) >= grade(s[i])) {
                    char op = ops.back();
                    ops.pop_back();
                    calc(op);
                }
                ops.push_back(s[i]);
            }
        }
        while (ops.size() && nums.size() >= 2) {
            char op = ops.back();
            ops.pop_back();
            calc(op);
        }
        auto val = nums.front()[0];
        return nums.front()[2 - val];
    }
};
