/*
每个数对应一个表示，预处理一下，对于每个查询递归构造答案即可
*/
#include <iostream>
using namespace std;
const int N = 2e4 + 10;

int n;
string f[N];

string get(int n) {
    if (n == 0) return "0";
    if (f[n].length() > 0) return f[n];
    bool first = true;
    for (int i = 15; i >= 0; i--) {
        if (n >> i & 1) {
            if (!first) f[n] += "+";
            if (i == 1)
                f[n] += "2";
            else if (i == 2)
                f[n] += "2(2)";
            else
                f[n] += "2(" + get(i) + ")";
            first = false;
        }
    }
    return f[n];
}
int main() {
    while (cin >> n) {
        cout << get(n) << endl;
    }
    return 0;
}
