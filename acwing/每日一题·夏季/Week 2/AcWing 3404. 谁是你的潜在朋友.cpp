#include <iostream>
using namespace std;
const int N = 210;

int n, m, p[N], s[N];
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        s[p[i]]++;
    }
    for (int i = 0; i < n; i++) {
        if (s[p[i]] == 1)
            puts("BeiJu");
        else
            cout << s[p[i]] - 1 << endl;
    }
    return 0;
}
