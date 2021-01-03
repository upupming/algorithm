/*
双向搜索
把礼物分成两半
搜索出前一半礼物中选出若干个，可能达到的 0 - W 之间的所有重量值，存放在一个数组 A 中，并对数组 A 进行排序，去重。
尝试从后一半礼物中选出一些，对于每个可能达到的重量值 t，在第一部分得到的数组 A 中二分查找 <= W - t 的数值中最大的一个，用二者的和更新答案

时间复杂度 O(2^{N/2} log2^{N/2} = O(N2^{N/2}))

优化技巧：
1. 礼物按照重量降序排序
2. 选择适当的折半划分点，稍微增加第一次搜索的礼物数，减少第二次搜索的二分次数

dfs(k, sum)
k: 当前枚举到第 k 个礼物
sum: 前面以选择的物品的重量之和
e: 全局变量，表示当前搜索的结束位置
*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;

int e, w, n, g[60];
vector<int> s, t;
void dfs(int k, LL sum, vector<int>& s) {
    if (k >= e + 1) {
        s.push_back(sum);
        return;
    }
    // 选这个
    if (sum + g[k] <= w) {
        dfs(k + 1, sum + g[k], s);
    }
    // 不选这个
    dfs(k + 1, sum, s);
}
int main() {
    cin >> w >> n;
    for (int i = 1; i <= n; i++) {
        cin >> g[i];
    }
    sort(g + 1, g + n + 1, greater<int>());
    e = n / 2 + 2;
    dfs(1, 0, s);
    sort(s.begin(), s.end());
    unique(s.begin(), s.end());
    e = n;
    dfs(n / 2 + 3, 0, t);
    unique(t.begin(), t.end());
    int ans = 0;
    for (auto& v : t) {
        // > 的位置
        auto it = upper_bound(s.begin(), s.end(), w - v);
        // <= 的位置
        it--;
        ans = max(ans, *it + v);
    }
    cout << ans << endl;
    return 0;
}