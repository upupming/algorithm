/*
注意「木棒」是没有砍断之前的，「木棍」是砍断之后的
// 正在拼木棒 stick，当前木棒长度为 cur，拼到木棒 stick 的上一根小木棍为 last
dfs(int stick, int cur, int last)

剪枝：
1. 将木棍从大到小排序，先尝试较长的木棍；同一根木棍搜索顺序等效，限制先后加入一根原始木棒的木棍长度是递减的
2. 如果当前木棒尝试过一个木棍并失败了，之后遇到相同的木棍直接跳过
3. 如果尝试拼入的第一根木棍的递归分支就返回失败，因为空木棒的等效性，后续一定不会成功，直接返回失败
4. 如果拼入一根之后恰好完整，并拼接接下来木棒的搜索失败，那么一定整个分支失败。贪心（A 刚好拼完当前木棒，A = B + C，先用 A 一定比先用 B, C 好）
*/
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 100;

// sub 为木棒长度数组，cnt 表示目标木棍数，len 表示每个木棍的长度
int n, sub[N], cnt, visited[N], len;
bool dfs(int stick, int cur, int last) {
    // 编号为 0 - cnt-1 木棒都拼好了
    if (stick == cnt) return true;
    // 当前已经拼好
    if (cur == len) return dfs(stick + 1, 0, -1);
    // 剪枝 2，记录尝试过的长度
    int fail = 0;
    // 枚举当前所有可选择的木棒
    for (int i = last + 1; i < n; i++) {
        if (!visited[i] && cur + sub[i] <= len && fail != sub[i]) {
            visited[i] = 1;
            if (dfs(stick, cur + sub[i], i)) return true;
            // 还原现场
            visited[i] = 0;

            fail = sub[i];
            // 剪枝 3, 4
            if (cur == 0 || cur + sub[i] == len) return false;
        }
    }
    // 已经尝试过所有分支，搜索失败
    return false;
}
int main() {
    while (cin >> n, n) {
        int maxSub = 0, sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> sub[i];
            maxSub = max(maxSub, sub[i]);
            sum += sub[i];
        }
        sort(sub, sub + n, greater<int>());
        for (len = maxSub; len <= sum; len++) {
            // 无法整除，不可能拼成
            if (sum % len) continue;
            // 目标是拼成 cnt 根长为 len 的木棍
            cnt = sum / len;
            // 每次新运行 dfs 都要清空 visited 数组
            memset(visited, 0, sizeof visited);
            if (dfs(0, 0, -1)) {
                cout << len << endl;
                break;
            }
        }
    }
}