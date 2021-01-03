/*
求两个字符串的最小表示即可，如果相等则表示同一个项链
书上讲过最小表示法，没例题，结果这么快就忘光了，赶紧实现一下
*/
#include <iostream>
using namespace std;

string a, b;
// 最小表示法模板
void getMinRep(string &s) {
    int n = s.length();
    s = s + s;
    int i = 0, j = 1;
    for (int k = 0; k < n && i < n && j < n; k++) {
        if (s[i + k] < s[j + k]) {
            j = j + k + 1;
            if (i == j) j++;
            k = -1;
        } else if (s[i + k] > s[j + k]) {
            i = i + k + 1;
            if (i == j) i++;
            k = -1;
        }
    }

    // cout << min(i, j) << endl;
    s = s.substr(min(i, j), n);
}
int main() {
    cin >> a >> b;
    getMinRep(a), getMinRep(b);
    if (a == b)
        puts("Yes"), cout << a << endl;
    else
        puts("No");
}