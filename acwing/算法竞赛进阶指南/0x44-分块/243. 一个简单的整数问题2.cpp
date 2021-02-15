/*
分块解决 RMQ 问题
对于整段的修改用 add 记录，对于不足整段的修改采取朴素算法
段数和段长都是 O(sqrt(N))，总时间复杂度是 O((N+Q)sqrt(N))
*/
#include <cmath>
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
typedef long long LL;

LL x, y, z, a[N], sum[N], add[N];
// 每段左右端点
int L[N], R[N];
// 每个位置属于哪一段
int pos[N];
int n, m, t;

void build() {
    // 分块，t 同时表示块大小和块个数
    t = sqrt(n);
    for (int i = 1; i <= t; i++) {
        L[i] = (i - 1) * t + 1;
        R[i] = i * t;
    }
    if (R[t] < n) t++, L[t] = R[t - 1] + 1, R[t] = n;
    // 预处理
    for (int i = 1; i <= t; i++) {
        for (int j = L[i]; j <= R[i]; j++) {
            pos[j] = i;
            sum[i] += a[j];
        }
    }
}

void change(int l, int r, long long d) {
    int p = pos[l], q = pos[r];
    // l 与 r 处于同一段，直接加在原数组和 sum 上
    if (p == q) {
        for (int i = l; i <= r; i++) a[i] += d;
        sum[p] += d * (r - l + 1);
    }
    // 开头结尾采用朴素算法，中间用 add 存储区间待加值
    // 注意要么加在 sum 上，要么加在 add 上，不要两者都加造成重复
    else {
        // 中间的完整块
        for (int i = p + 1; i <= q - 1; i++) add[i] += d;
        // 开头不构成一个块的区间：[l, R[p]]
        for (int i = l; i <= R[p]; i++) a[i] += d;
        sum[p] += d * (R[p] - l + 1);
        // 结尾不构成一个块的区间：[L[q], r]
        for (int i = L[q]; i <= r; i++) a[i] += d;
        sum[q] += d * (r - L[q] + 1);
    }
}
long long ask(int l, int r) {
    int p = pos[l], q = pos[r];
    long long ans = 0;
    if (p == q) {
        for (int i = l; i <= r; i++) ans += a[i];
        ans += add[p] * (r - l + 1);
    } else {
        // 中间的完整块
        for (int i = p + 1; i <= q - 1; i++) ans += sum[i] + add[i] * (R[i] - L[i] + 1);
        // 开头不构成一个块的区间：[l, R[p]]
        for (int i = l; i <= R[p]; i++) ans += a[i];
        ans += add[p] * (R[p] - l + 1);
        // 结尾不构成一个块的区间：[L[q], r]
        for (int i = L[q]; i <= r; i++) ans += a[i];
        ans += add[q] * (r - L[q] + 1);
    }
    return ans;
}

string s;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build();
    while (m--) {
        cin >> s;
        if (s[0] == 'Q') {
            cin >> x >> y;
            cout << ask(x, y) << endl;
        } else {
            cin >> x >> y >> z;
            change(x, y, z);
        }
    }
    return 0;
}
