/*
有埃式筛法和线性筛法两种
*/
#include <iostream>
using namespace std;
const int N = 1e6 + 10;
int primes[N], cnt;
bool st[N];

// 埃式筛法
// 每个数 i 会筛 (n/i) 个数，只会考虑 O(n / ln n) 个质数的倍数，最坏时间复杂度为 O(n log n)，实际复杂度为 O(n log log n)
void get_primes_e(int n) {
    for (int i = 2; i <= n; i++) {
        if (st[i]) continue;
        // i 没有被筛掉，所以就是素数
        primes[cnt++] = i;
        // 筛掉 i 的所有倍数
        for (int j = i + i; j <= n; j += i) {
            st[j] = true;
        }
    }
}
// 埃式筛法优化
// 对于每个 x，只需要从 x^2 筛起，其他的被更小的数已经筛过了，时间复杂度还是 O(n log log n)
void get_primes_e1(int n) {
    for (int i = 2; i <= n; i++) {
        if (st[i]) continue;
        // i 没有被筛掉，所以就是素数
        primes[cnt++] = i;
        // 筛掉 i 的所有倍数
        for (int j = i; j <= n / i; j += 1) {
            st[j * i] = true;
        }
    }
}

// 线性筛法
// 每个数只会被自己的最小质因子筛掉，时间复杂度为 O(n)
void get_primes_l(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        // j < cnt 没有必要，因为 i 是合数的时候，枚举到最小质因子一定会 break
        // 如果 i 是质数 primes[j] == i 的时候也会停止循环
        for (int j = 0; primes[j] <= n / i; j++) {
            // primes[j] 是 primes[j] * i 的最小质因子
            st[primes[j] * i] = true;
            // primes[j] 一定是 i 的最小质因子（因为 y 是从小到大枚举的）
            if (i % primes[j] == 0) break;
        }
    }
}

int n;
int main() {
    cin >> n;
    get_primes_l(n);
    cout << cnt << endl;
    return 0;
}
