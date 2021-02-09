#include <algorithm>
#include <iostream>
using namespace std;

int n;
string toString(int x) {
    string ans;
    while (x) {
        int remainder = x % n;
        ans += remainder >= 10 ? remainder - 10 + 'A' : remainder + '0';
        x /= n;
    }
    return ans;
}
int main() {
    cin >> n;
    for (int x = 1; x <= 300; x++) {
        int y = x * x;
        string a = toString(y), b = a;
        reverse(b.begin(), b.end());
        if (a == b) {
            string c = toString(x), d = c;
            reverse(d.begin(), d.end());
            cout << d << " " << b << endl;
        }
    }
    return 0;
}