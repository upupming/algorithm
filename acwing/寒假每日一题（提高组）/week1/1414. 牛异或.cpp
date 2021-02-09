/*
首先算出前缀异或和 sum，则 sum[i] 异或（减） sum[j] 就是从 j+1 到 i 的所有值的异或结果（注意异或加减都是等价的）
这样问题就变成了从 sum 中找两个数，他们有最大的异或值
这个问题就是 AcWing 143. 最大异或对了
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10, M = 23 * N + 10;

int n, a, sum;
// idx[p] 表示叶子节点 p 代表的数在原序列中的下标
int trie[M][2], tot = 1, idx[M];
int main() {
    cin >> n;
    int st, ed, ans = -1;
    int p = 1;
    // 插入 sum[0] = 0
    for (int j = 22; j >= 0; j--) {
        trie[p][0] = ++tot;
        p = trie[p][0];
    }
    idx[p] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        sum = sum ^ a;
        // 将 sum 插入到 trie 中
        int p = 1, q = 1;
        int tmp = 0;
        for (int j = 22; j >= 0; j--) {
            int b = sum >> j & 1;
            // 插入节点
            if (!trie[p][b]) trie[p][b] = ++tot;
            p = trie[p][b];
            // 寻找匹配，能够匹配一个不同的位的话
            if (trie[q][!b]) {
                tmp |= 1 << j;
                q = trie[q][!b];
            } else {
                // 因为一定至少有一条路径，所以这个方向是一定可以走的
                q = trie[q][b];
            }
        }
        // 注意这里是严格大于，因为「如果存在多个这样的序列，那么选择序列末端整数对应的奶牛编号更小的那个序列」
        if (tmp > ans) {
            ans = tmp;
            // st 要 +1，这是因为 sum[j] - sum[i] 最大的话，实际对应的数的范围是 [i+1, j]
            ed = i, st = idx[q] + 1;
        }
        // 标记 idx，注意这里两个相同的 sum 可能会产生覆盖，后面的会覆盖前面的，刚好满足题目要求，即「长度最短的那个序列」（这样 st 会尽量大）
        idx[p] = i;
    }
    cout << ans << " " << st << " " << ed << endl;
    return 0;
}