/*
数位 dp
https://www.acwing.com/solution/content/31142/
满足题目要求的数，B 进制表示下每一位要么是 0，要么是 1（因为要求恰好是 B 的整数次幂）
用 dp(n) 表示 1-n 里面满足要求的数目，dp(y) - dp(x-1) 就是最终答案
按照位数从高往低枚举，例如：76543210，最高位到最低位依次为 a_7, ..., a_0
枚举 7 这一位时：
1. 选择填 7（a_i）
    如果 a_i > 1，这个方案是不合法的，因为
    如果 a_i == 1，那么剩余位置还需要放 k-1 个 1
2. 选择填 0-6 （0~(a_i - 1)）
    后面怎么填都不会超过上限 n
    如果 a_i 填的是 0，那么剩余位置还需要放 k 个 1，用组合数求
    如果 a_i 填的是 1，那么剩余位置还需要放 k-1 个 1，用组合数求
    其他方案在这题中均不合法，可以忽略

时间复杂度：O(log N)
*/
#include <iostream>
#include <vector>
using namespace std;
const int N = 35;

int c[N][N];
int x, y, k, b;
// 计算组合数
void cbp() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0)
                c[i][j] = 1;
            else
                // 两种情况：选第 1 个数和不选第 1 个数
                c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }
    }
}
int dp(int n) {
    if (!n) return 0;
    vector<int> num;
    while (n) num.push_back(n % b), n /= b;
    // one 表示已经填了多少个 1
    int ans = 0, one = 0;
    // 从高位往低位枚举
    for (int i = num.size() - 1; i >= 0; i--) {
        int t = num[i];
        // cout << t << " ";
        // 左边的分支（0 - (a_i - 1)）
        if (t) {
            // 左边填 0
            ans += c[i][k - one];
            // 只有 t > 1 时才能枚举左边填 1 的情况，t == 1 的话，只能去后面的位分支
            if (t > 1) {
                // 左边填 1 的情况
                if (k - one - 1 >= 0) ans += c[i][k - one - 1];
                // 填 0 和 1 的情况都算完了，其他情况都不可能了，直接 break
                break;
            } else {
                // t = 1 时可以进入右边的分支再继续分类讨论
                one++;
                // 如果已经超过 k 了，继续看后面的位已经没有意义，直接 break
                if (one > k) break;
            }
        }
        // 最右侧分支上的方案：进行到底了，那么也算一种方案数，算上
        if (i == 0 && one == k) ans++;
    }
    // cout << endl;
    return ans;
}
int main() {
    cin >> x >> y >> k >> b;
    cbp();
    cout << dp(y) - dp(x - 1) << endl;
    return 0;
}
