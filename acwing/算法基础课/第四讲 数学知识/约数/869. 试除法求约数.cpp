/*
分解质因数 p1, p2, ..., pk
那么所有的约数就是 p1^i1 * ... * pK^ik
*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n, x;
vector<int> get_divisors(int x) {
    vector<int> res;
    for (int i = 1; i <= x / i; i++) {
        if (x % i == 0) {
            res.push_back(i);
            if (i != x / i) res.push_back(x / i);
        }
    }
    sort(res.begin(), res.end());
    return res;
}
int main() {
    cin >> n;
    while (n--) {
        cin >> x;
        auto res = get_divisors(x);

        for (auto x : res) cout << x << ' ';
        cout << endl;
    }
    return 0;
}
