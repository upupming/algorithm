// https://www.geeksforgeeks.org/find-the-nearest-smaller-numbers-on-left-side-in-an-array/

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// stack method, O(n) time
vector<int> calLeftFirstSmaller(const vector<int> &a) {
    stack<int> s;
    vector<int> b(a.size(), -1);
    s.push(a[0]);
    for (int i = 1; i < a.size(); i++) {
        while (!s.empty() && s.top() >= a[i]) s.pop();
        if (s.empty())
            b[i] = -1;
        else
            b[i] = s.top();
        s.push(a[i]);
    }
    return b;
}

int main() {
    //           {_, 1, 1,  4, 1, 2}
    vector<int> a{1, 6, 4, 10, 2, 5};
    vector<int> b = calLeftFirstSmaller(a);
    for (auto x : b) cout << " " << x;
    cout << endl;
    return 0;
}