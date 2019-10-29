#include <iostream>

using namespace std;

int n, n1, n2;
string str;

int main() {
    cin >> str;
    n = str.length();
    for (n1 = n / 2; n1 >= 0; n1 --) {
        n2 = n + 2 - 2 * n1;
        if (n1 <= n2 && n2 >= 3 && n2 <= n) break;
    }
    for (int i = 0; i < n1 - 1; i++) {
        cout << str[i];
        for (int j = 0; j < n2 - 2; j++) cout << " ";
        cout << str[n - 1 - i] << endl;
    }
    for (int i = 0; i < n2; i++) {
        cout << str[n1 -1 + i];
    }
    return 0;
}