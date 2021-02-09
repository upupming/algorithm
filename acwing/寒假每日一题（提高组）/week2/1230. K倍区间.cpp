/*
前缀和，但是要优化到 O(N log N) 才行
枚举所有区间的右端点 i，查找所有满足 S[j] % k == S[i] % k 的左端点即可。
存取模的结果可以用哈希表。
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;

int cnt[N], sum, a, n, k;
long long ans;
int main() {
    cin >> n >> k;
    // 处理 sum[0] = 0
    cnt[0]++;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        sum = (sum + a) % k;
        ans += cnt[sum]++;
    }
    cout << ans << endl;
    return 0;
}