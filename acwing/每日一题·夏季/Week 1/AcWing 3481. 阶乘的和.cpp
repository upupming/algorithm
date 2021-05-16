#include <iostream>
#include <set>
#include <vector>

using namespace std;
const int N = 1e6 + 10;

set<int> s;
vector<int> v;

int main() {
    v.push_back(1);
    for (int i = 1; i <= 12; i++) {
        int a = v.back() * i;
        v.push_back(a);
    }

    for (int i = 1; i < 1 << 12; i++) {
        int t = 0;
        for (int j = 0; j < 12; j++) {
            if (i >> j & 1) {
                t += v[j];
            }
        }
        s.insert(t);
    }

    int x;
    while (cin >> x && x >= 0) {
        if (s.count(x))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}
