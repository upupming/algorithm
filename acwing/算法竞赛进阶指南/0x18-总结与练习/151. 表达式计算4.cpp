/*
中缀表达式求值，有两种做法：
1. 转换为后缀表达式再求值：O(N)
2. 递归法求值：O(N^2)
这里使用方法 1
注意这个题目还要处理负数的符号位的情况，例如 -3+1
- 到底是负号还是减号?
特例：
((((((-1)
(-1)))
(2+2)^(-(1+1)+2)
*/
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

vector<int> nums;
vector<char> ops;
string s;

// 优先级
int grade(char op) {
    switch (op) {
        case '(':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        case '^':
            return 4;
    }
    return 0;
}
// 处理后缀表达式中的一个运算符
void calc(char op) {
    // 从栈顶取出两个数
    int y = nums.back();
    nums.pop_back();
    int x;
    // 如果出现负号的情况：
    if (
        // 1. 可能没有多的操作数了，前一个操作数当做 0 看待
        !nums.size() ||
        // 2. 可能前面是左括号 (，需要先把这个负数计算出来（补一个 0 利用，0 - y = -y）
        (op == '-' && ops.size() && ops.back() == '(')) {
        x = 0;
    } else {
        x = nums.back();
        nums.pop_back();
    }
    int z;
    switch (op) {
        case '+':
            z = x + y;
            break;
        case '-':
            z = x - y;
            break;
        case '*':
            z = x * y;
            break;
        case '/':
            z = x / y;
            break;
        case '^':
            z = pow(x, y);
    }
    // cout << x << op << y << " = " << z << endl;
    // 把运算结果放回栈中
    nums.push_back(z);
}
int main() {
    cin >> s;
    int val = 0, n = s.length();
    for (int i = 0; i < n; i++) {
        // 多位数， 并且表达式是使用字符串逐字符存储的，我们只需要稍加判断，把连续的一段数字看成一个数即可。
        if (s[i] >= '0' && s[i] <= '9') {
            val = val * 10 + s[i] - '0';
            if (i + 1 < n && s[i + 1] >= '0' && s[i + 1] <= '9') continue;
            // 后缀表达式的一个数，直接入栈
            nums.push_back(val);
            val = 0;
        }
        // 左括号：直接入栈
        else if (s[i] == '(') {
            ops.push_back('(');
        }
        // 右括号：一直出栈直到遇见左括号
        else if (s[i] == ')') {
            while (ops.size() && ops.back() != '(') {
                // 出栈一个符号就计算一下
                char op = ops.back();
                ops.pop_back();
                calc(op);
            }
            // 左括号出栈（如果有的话）
            if (ops.size()) ops.pop_back();
        }
        // 运算符：只要栈顶符号的优先级不低于新符号，就不断取出栈顶并输出，最后把新符号进栈，其实只在这里使用了优先级的比较
        else {
            while (ops.size() && grade(ops.back()) >= grade(s[i])) {
                char op = ops.back();
                ops.pop_back();
                calc(op);
            }
            ops.push_back(s[i]);
        }
    }
    // 剩下符号再计算一下
    while (ops.size() && nums.size() >= 2) {
        char op = ops.back();
        ops.pop_back();
        calc(op);
    }
    // 后缀表达式栈中最后剩下的数就是答案
    cout << nums.front() << endl;
    return 0;
}
