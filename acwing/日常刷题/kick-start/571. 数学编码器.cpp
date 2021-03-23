/*
暴力解法：枚举所有的子集，时间复杂度为 O(2^n)
优化解法：
对于每个元素 k[i]，作为最大值的次数为 x，作为最小值得次数为 y，那么对答案的贡献就是 (x-y) * k[i]
所有数字排序之后，k[i] 左侧有 i 个数，每个数可选可不选，共 2^i 中方案；右侧有 n-1-(i+1)+1 = n-1-i 个数，共 2^{n-1-i} 种方案。
对于有相同数的情况，规定选择最小数为最左侧的那个，最大数为最右侧的那个，这样不影响答案的计算，仍然使用上述算法，最终的答案保证不重不漏
时间复杂度：O(n)
*/
#include <iostream>
using namespace std;
const int P = 1e9 + 7, N = 1e4 + 10;

int t, n, k, pow[N];
int main() {
    pow[0] = 1;
    for (int i = 1; i < N; i++) {
        pow[i] = pow[i - 1] * 2 % P;
    }

    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            cin >> k;
            int x = i, y = n - 1 - i;
            ans = (ans + 1ll * (pow[x] - pow[y]) * k) % P;
        }
        printf("Case #%d: %d\n", i, ans);
    }
    return 0;
}
