/*
类似前缀和，可以存一个前缀最小值，也用栈就行
*/

#include <stack>
using namespace std;
class MinStack {
   public:
    stack<int> a, b;
    /** initialize your data structure here. */
    MinStack() {
    }

    void push(int x) {
        a.push(x);
        int minTop = x;
        if (!b.empty()) minTop = min(b.top(), minTop);
        b.push(minTop);
    }

    void pop() {
        a.pop();
        b.pop();
    }

    int top() {
        return a.top();
    }

    int getMin() {
        return b.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */