#include <assert.h>
#include <iostream>
#include <stack>

using namespace std;

class MyQueue {
  stack<int> s1, s2;

 public:
  void push(int val) { s1.push(val); }
  int front() {
    if (!s2.empty()) return s2.top();
    while (!s1.empty()) {
      int a = s1.top();
      s1.pop();
      s2.push(a);
    }
    assert(!s2.empty());
    return s2.top();
  }
  void pop() {
    if (!s2.empty()) return s2.pop();
    while (!s1.empty()) {
      int a = s1.top();
      s1.pop();
      s2.push(a);
    }
    assert(!s2.empty());
    s2.pop();
  }
};

int main() {
  MyQueue q;
  q.push(1);
  q.push(2);
  q.push(3);
  q.push(4);
  int a = q.front();
  printf("%d\n", a);
  q.pop();
  a = q.front();
  printf("%d\n", a);
  return 0;
}
