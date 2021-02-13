/*
对于 v 图腾来说：
1. 倒序扫描 a[i]，求 a[i] 后边有几个数比它大，记为 left[i]
2. 正序扫描 a[i]，求 a[i] 前面有几个数比它大，记为 right[i]
3. 结果就是 \sigma left[i] * right[i]
对于 ^ 图腾来说：
只需要把比较符号换一下即可
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 2e5 + 10;
typedef long long LL;

LL n, a[N], c[N], maxA;
LL ask(LL x) {
    LL ans = 0;
    for (; x; x -= x & -x) ans += c[x];
    return ans;
}
void add(LL x, LL y) {
    for (; x <= N; x += x & -x) c[x] += y;
}
LL calc(bool is_v) {
    LL ans = 0;
    LL left[N], right[N];
    memset(c, 0, sizeof c);
    // 倒序扫描
    for (int i = n; i; i--) {
        if (is_v)
            right[i] = ask(maxA) - ask(a[i]);
        else
            right[i] = ask(a[i] - 1);
        add(a[i], 1);
    }
    memset(c, 0, sizeof c);
    // 正序扫描
    for (int i = 1; i <= n; i++) {
        if (is_v)
            left[i] = ask(maxA) - ask(a[i]);
        else
            left[i] = ask(a[i] - 1);
        add(a[i], 1);

        ans += left[i] * right[i];
    }
    return ans;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        maxA = max(maxA, a[i]);
    }
    cout << calc(true) << " " << calc(false) << endl;
    return 0;
}