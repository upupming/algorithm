/*
那么任意一个约数可以写成 p1^i1 * ... * pk^ik，其中 0 <= ik < c_k
约数之和就是 (1 + p1 + p1^2 + ... + p1^c_1) * ... * (1 + pk + pk^2 + ... + pk^ck)
*/
#include <iostream>
#include <unordered_map>
using namespace std;
const int P = 1e9 + 7;

int n, a;
unordered_map<int, int> mp;
void divide(int x) {
    for (int i = 2; i <= x / i; i++) {
        // 如果 x % i == 0，i 一定是质数，否则已经被分解过了
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) x /= i, s++;
            mp[i] += s;
        }
    }
    // 最后剩下一个大于 sqrt(x) 的约数
    if (x > 1) mp[x] += 1;
}

int main() {
    cin >> n;
    while (n--) {
        cin >> a;
        divide(a);
    }

    int ans = 1;
    for (auto &p : mp) {
        long long x = 1;
        for (int i = 0; i < p.second; i++) {
            x = (x * p.first + 1) % P;
        }
        ans = ans * x % P;
    }
    cout << ans << endl;
    return 0;
}
