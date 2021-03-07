/*
1. dp, i 表示未进栈个数，j 表示栈内个数，f[i][j] = f[i-1][j+1] + f[i][j-1]，初始条件 f[0][0] = 1，目标 f[n][0]；dp 做法会 TLE，复杂度 O(n^2)

Catalan 数：C_{2n}^{n}/(n+1)
优化 1：在组合数的计算过程中，进行素数分解操作，先算一下结果中各个素数的次数，再计算乘积，需要用到线性筛素数算法和质数分解算法（n! 中 2 的次数为 n/2 + n/4 + n/8 + ...）
优化 2：高精度乘法，压位（就是把 10 进制换成 10^4 或者 10^8 进制，压 8 位需要用 long long）
*/

#include <iostream>
#include <vector>
using namespace std;

// 压位数
int base = 1e9;
typedef long long LL;

void multi(vector<LL> &a, int b) {
    int t = 0;
    for (int i = 0; i < a.size(); i++) {
        a[i] = t + a[i] * b;
        t = a[i] / base;
        a[i] = a[i] % base;
    }
    while (t) {
        a.push_back(t % base);
        t /= base;
    }
}

void out(vector<LL> &a) {
    cout << a[a.size() - 1];
    for (int i = a.size() - 2; i >= 0; i--) {
        printf("%09lld", a[i]);
    }
    cout << endl;
}

int n;
// st[i] 为 true 表示 i 已经被筛除
int primes[120010], st[120010], cnt;
// 预处理 2n 内的所有素数
void calPrimes() {
    // 时间复杂度 O(n(1 + 1/2 + ... 1/n) = n ln n)
    for (int i = 2; i <= 2 * n; i++) {
        if (!st[i]) {
            primes[cnt++] = i;
            // 筛除所有倍数
            for (int j = 2 * i; j <= 2 * n; j += i) {
                st[j] = true;
            }
        }
    }
}
int powers[120010];

// 返回 n 里面有多少因子 p
int getTimes(int n, int p) {
    int ans = 0;
    while (n) {
        ans += n / p;
        n /= p;
    }
    return ans;
}

int main() {
    cin >> n;
    calPrimes();
    // 分解质因数
    for (int i = 0; i < cnt; i++) {
        int p = primes[i];
        powers[p] = getTimes(2 * n, p) - 2 * getTimes(n, p);
    }
    // 还要除以 (n+1)
    int k = n + 1;
    for (int i = 0; i < cnt && primes[i] <= k; i++) {
        int p = primes[i], s = 0;
        while (k % p == 0) {
            s++;
            k /= p;
        }
        powers[p] -= s;
    }
    vector<LL> ans(1, 1);
    for (int i = 2; i <= 2 * n; i++) {
        for (int j = 0; j < powers[i]; j++)
            multi(ans, i);
    }
    out(ans);
    return 0;
}

/*
dp 做法（TLE）：
vector<int> f[3][60010];
int main() {
    cin >> n;
    for (int j = 0; j <= n; j++) {
        f[0][j] = vector<int>(1, 1);
    }
    vector<int> zero(1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            f[1][j] = add(f[0][j + 1], j > 0 ? f[1][j - 1] : zero);
        }
        // copy 一下
        for (int j = 0; j < n; j++) {
            f[0][j] = f[1][j];
        }
    }
    for (int i = f[0][0].size() - 1; i >= 0; i--) {
        cout << f[0][0][i];
    }
    cout << endl;
    return 0;
}
*/
