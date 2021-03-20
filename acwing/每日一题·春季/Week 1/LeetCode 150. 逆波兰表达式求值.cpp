#include <bits/stdc++.h>
using namespace std;

void eval(stack<int>& nums, char c) {
    auto b = nums.top();
    nums.pop();
    auto a = nums.top();
    nums.pop();
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
class Solution {
   public:
    int evalRPN(vector<string>& tokens) {
        stack<int> nums;
        for (int i = 0; i < tokens.size(); i++) {
            auto t = tokens[i];
            if (t == "+" || t == "-" || t == "*" || t == "/") {
                eval(nums, t[0]);
            } else {
                nums.push(stoi(t));
            }
        }
        return nums.top();
    }
};
