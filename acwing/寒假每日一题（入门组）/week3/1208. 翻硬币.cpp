#include <iostream>
using namespace std;

string s, t;
int a = '*', b = 'o', c = a + b;
int main() {
    cin >> s >> t;
    int n = s.length(), cnt = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] != t[i]) {
            s[i] = c - s[i];
            s[i + 1] = c - s[i + 1];
            cnt++;
        }
    }
    cout << cnt << endl;
}