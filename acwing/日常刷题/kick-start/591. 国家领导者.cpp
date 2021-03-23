/*
https://codingcompetitions.withgoogle.com/kickstart/round/0000000000201ca2/0000000000201d30

读取带有空格的一行可以使用 getline
常用技巧是使用 while 循环来过滤掉空行：https://www.geeksforgeeks.org/how-to-use-getline-in-c-when-there-are-black-lines-in-input/
为什么 cin 之后 getline 会多一个空行：https://stackoverflow.com/a/21567292
可以用 ws 来删除前导空字符

线性扫描 + 自定义比较符
*/
#include <iostream>
#include <unordered_set>
using namespace std;

int t, n;

// true: now 比 ans 更好
bool cmp(string& now, string& ans) {
    unordered_set<char> s1, s2;
    for (auto& c : now) {
        if (c != ' ') s1.insert(c);
    }
    for (auto& c : ans) {
        if (c != ' ') s2.insert(c);
    }
    if (s1.size() == s2.size()) {
        return now < ans;
    }
    return s1.size() > s2.size();
}
string solve() {
    cin >> n;
    string ans, now;
    for (int i = 0; i < n; i++) {
        // 注意这里一定要消除空白字符，否则数字后面的回车符会被误读进来
        getline(cin >> ws, now);
        if (i == 0)
            ans = now;
        else if (cmp(now, ans))
            ans = now;
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: %s\n", i, solve().c_str());
    }
    return 0;
}
