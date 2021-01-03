#include <iostream>
#include <unordered_map>
using namespace std;

/*
给定最高的牛，先初始化
  index: 1 2 3 4 5 6 7 8 9
原数组 a: 5 5 5 5 5 5 5 5 5
差分后 b: 5 0 0 0 0 0 0 0 0

每遇到一个条件就更新差分数组，例如：
3 7 可以互相看到，更新为：
  index: 1 2 3  4 5 6 7 8 9
差分后 b: 5 0 0 -1 0 0 1 0 0
原数组 a: 5 5 5  4 4 4 5 5 5

每次只需要更新差分数组的两个元素，所以时间复杂度从直接操作原数组的 O(n) 降到了 O(1)。
最后利用差分数组重构原数组即可，差分、前缀和互为逆操作。
*/

int n, p, h, m, a, b, diff[10010];
unordered_map<int, unordered_map<int, bool>> seen;
int main() {
    cin >> n >> p >> h >> m;
    diff[1] = h;
    while (m--) {
        cin >> a >> b;
        if (a > b) swap(a, b);
        if (!seen[a][b])
            diff[a + 1]--, diff[b]++;
        // 防止重复 seen，只计算一次
        seen[a][b] = true;
    }

    for (int i = 1; i <= n; i++)
        cout << (diff[i] += diff[i - 1]) << endl;
}