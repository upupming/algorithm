#include <iostream>
#include <algorithm>

using namespace std;
// 千万不要因为题目简单而错理解题意
string s, t;

int main() {
    cin >> s;
    reverse(s.begin(), s.end());
    t = s;
    int carry = 0;
    for (int i = 0; i < s.length(); i++) {
        int bit = 2 * (s[i] - '0') + carry;
        carry = bit / 10;
        t[i] = (bit % 10) + '0';
    }
    sort(s.begin(), s.end());
    string u = t; reverse(u.begin(), u.end());;
    sort(t.begin(), t.end());
    if (carry == 1 || t != s) cout << "No" << endl;
    else cout << "Yes" << endl;
    if (carry) cout << "1";
    cout << u << endl;
    return 0;
}
