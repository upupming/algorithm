#include <iostream>
using namespace std;

string s, t;
int main() {
    cin >> s;
    t = s.substr(0, 1) + s.substr(2, 3) + s.substr(6, 5);
    // cout << t << endl;
    char last = s[s.length() - 1];
    int e = last == 'X' ? 10 : last - '0', a = 0;
    for (int i = 0; i < t.length(); i++) {
        a += (t[i] - '0') * (i + 1);
    }
    a = a % 11;
    s = s.substr(0, s.length() - 1);
    s += a == 10 ? 'X' : '0' + a;
    if (e == a)
        cout << "Right" << endl;
    else
        cout << s << endl;
    return 0;
}