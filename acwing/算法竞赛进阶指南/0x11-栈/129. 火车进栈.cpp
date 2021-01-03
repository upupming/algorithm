/*
dfs 解决，注意枚举顺序
*/
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int n, cnt;
stack<int> s;
vector<int> ans;
int x = 1;
void dfs1() {
    // 终止情况
    if (x > n && s.empty() && cnt++ < 20) {
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i];
        }
        cout << endl;
    }

    if (!s.empty()) {
        // case 1: s 顶出栈
        ans.push_back(s.top());
        s.pop();
        dfs1();
        s.push(ans.back());
        ans.pop_back();
    }
    if (x <= n) {
        // case 2: n 进栈
        s.push(x);
        x++;
        dfs1();
        x--;
        s.pop();
    }
}
void dfs(stack<int>& s, vector<int>& ans, int x) {
    // 终止情况
    if (x > n && s.empty() && cnt++ < 20) {
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i];
        }
        cout << endl;
    }

    if (!s.empty()) {
        // case 1: s 顶出栈
        ans.push_back(s.top());
        s.pop();
        dfs(s, ans, x);
        s.push(ans.back());
        ans.pop_back();
    }
    if (x <= n) {
        // case 2: n 进栈
        s.push(x);
        dfs(s, ans, x + 1);
        s.pop();
    }
}
int main() {
    cin >> n;
    // dfs(s, ans, 1);
    dfs1();
    return 0;
}