/*
阶乘 + 逆元
c[a][b] = (a!)/(b!(a-b)!)
除以阶乘等于乘以阶乘的逆元
逆元是 log 的时间复杂度，因此总的时间复杂度是 n log P 的
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10, P = 1e9 + 7;

int qpow(int a, int b, int p) {
    int ans = 1 % p;
    while (b) {
        if (b & 1)
            ans = 1ll * ans * a % p;
        b >>= 1;
        a = 1ll * a * a % p;
    }
    return ans;
}

long long fact[N], infact[N];
int n, a, b;
int main() {
    // 0! = 1，逆元也是 1，参考：https://www.zhihu.com/question/57705095
    // 0^{p-2} = 1，也就是说 0 的逆元是 1
    fact[0] = infact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % P;
        infact[i] = infact[i - 1] * qpow(i, P - 2, P) % P;
    }
    cin >> n;
    while (n--) {
        cin >> a >> b;
        cout << (fact[a] * infact[b] % P) * infact[a - b] % P << endl;
    }
    return 0;
}
