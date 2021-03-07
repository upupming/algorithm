/*
火车进栈有用到过，高精度+分解质因数
有多少个 p: a/p + a/p^2 + ...
1, 2, 3, 4, 5, 6, 7, 8, 9, 10
   -     -     -     -     -    10/2=5
         -           -          10/4=2
                     -          10/8=1
10! 中，质数 2 的总个数为 5 + 2 + 1 = 8
*/
#include <iostream>
#include <vector>
using namespace std;
const int N = 5e3 + 10;

int primes[N], cnt, sum[N];
bool st[N];
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

int get(int n, int p) {
    int ans = 0;
    while (n) {
        ans += n / p;
        n /= p;
    }
    return ans;
}

vector<int> mul(vector<int> a, int b) {
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size(); i++) {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    while (t) {
        c.push_back(t % 10);
        t /= 10;
    }
    return c;
}

int a, b;
int main() {
    cin >> a >> b;
    get_primes_l(a);

    for (int i = 0; i < cnt; i++) {
        int p = primes[i];
        sum[i] = get(a, p) - get(a - b, p) - get(b, p);
    }

    vector<int> ans;
    ans.push_back(1);

    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < sum[i]; j++) {
            ans = mul(ans, primes[i]);
        }
    }

    for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i];
    cout << endl;

    return 0;
}
