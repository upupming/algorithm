#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;

string s;
stack<int> nums;
stack<char> op;

void eval() {
    auto b = nums.top();
    nums.pop();
    auto a = nums.top();
    nums.pop();
    auto c = op.top();
    op.pop();
    int x;
    if (c == '+')
        x = a + b;
    else if (c == '-')
        x = a - b;
    else if (c == '*')
        x = a * b;
    else if (c == '/')
        x = a / b;
    nums.push(x);
}

unordered_map<char, int> pr{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

int main() {
    cin >> s;
    for (int i = 0; i < s.size(); i++) {
        auto c = s[i];
        if (isdigit(c)) {
            int x = 0, j = i;
            while (j < s.size() && isdigit(s[j]))
                x = x * 10 + s[j++] - '0';
            i = j - 1;
            nums.push(x);
        } else if (c == '(')
            op.push(c);
        else if (c == ')') {
            while (op.top() != '(') eval();
            op.pop();
        } else {
            while (op.size() && pr[op.top()] >= pr[c]) eval();
            op.push(c);
        }
    }
    while (op.size()) eval();
    cout << nums.top() << endl;
    return 0;
}
