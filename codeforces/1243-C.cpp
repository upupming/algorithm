
#include <iostream>
#include <set>
#include <assert.h>
 
using namespace std;
 
long long isPrime(long long n) {
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0 && isPrime(i) == -1) return i;
    }
    return -1;
}
 
long long findQ(long long n, long long p) {
    long long powPK = p;
    // 直接用 math 里面的 pow 在 codeforces 里面会失去精度
    // https://codeforces.com/blog/entry/1521
    while (powPK < n) powPK *= p;
    if (powPK == n) return p;
    else {
        assert(powPK > n);
        return 1L;
    }
}
 
long long n;
int main() {
    cin >> n;
    long long p = isPrime(n);
    if (p == -1) {
        cout << n << endl;
    } else {
        cout << findQ(n, p) << endl;
    }
    return 0;
}