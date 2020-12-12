/*
单调队列

根据数据范围，只能用线性时间的复杂度的算法
首先求一下前缀和，枚举所有右端点 i，看所有可能的左端点 [i-m, i-1]，假设有两个左端点 j, k 可选，j < k 但是 s[j] > s[k] 的话，可以直接淘汰 j，因为用 k 序列长度不仅小，序列和还更大。所有可能的左端点用队列维护，那么这个队列的前缀和一定是单调递增的。也就是说队首就是最优决策。
关键在于如何维护所有可能的左端点，i 增加的时候，需要从队首删去长度大于 m 的左端点，同时从队尾开始一直删掉那些前缀和大于 s[i] 的即可。所以需要用双端队列 deque。
*/
#include <deque>
#include <iostream>
using namespace std;

typedef pair<int, int> PII;
int n, m, a, sum, ans = 0x80000000;
deque<PII> dq;
int main() {
    cin >> n >> m;
    dq.emplace_back(0, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a, sum += a;
        // 队首一直出队直到满足 <=m 条件
        while (!dq.empty() && (i - dq.front().second > m)) {
            dq.pop_front();
        }
        if (dq.empty()) {
            ans = max(ans, sum);
        } else {
            ans = max(ans, sum - dq.front().first);
            // 不断删除队尾的不会优于当前 i 的左端点
            while (!dq.empty() && dq.back().first >= sum) dq.pop_back();
        }
        dq.emplace_back(sum, i);
        // cout << i << " " << sum << " " << ans << endl;
    }
    cout << ans << endl;
}