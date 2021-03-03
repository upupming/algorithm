/*
a 的所有质因数为 p1, ..., pk，次数为 c1, ..., c_k
那么任意一个约数可以写成 p1^i1 * ... * pk^ik，其中 0 <= ij < c_j
所以总的约数个数为 (c1+1) * ... * (c_k + 1)

直接 copy 一下分解质因数的代码，改一下即可
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
        ans = ans * (p.second + 1ll) % P;
    }
    cout << ans << endl;
    return 0;
}
