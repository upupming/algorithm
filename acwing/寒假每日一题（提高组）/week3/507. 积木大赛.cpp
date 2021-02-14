/*
区间增加等价于差分数组中，首尾发生变化

2 3 4 1 2
目标差分：
2 1 1 -3 1
起始差分：
0 0 0 0  0
第 1 步：
1 0 0 -1 0
第 2 步：
1 1 0 -2 0
第 3 步：
1 1 1 -3 0
第 4 步：
2 1 1 -3 0 -1
第 5 步：
2 1 1 -3 1 -2

从 2 1 1 -3 1 -2 开始考虑：
每个正数可以在后面匹配一个数
最终结果：max(sum(+), sum(-))
但是最终结果一定是正数，所以结果就是 sum(+)
*/
#include <iostream>
using namespace std;

int n, last, a, ans;
int main() {
    cin >> n;
    while (n--) {
        cin >> a;
        int diff = a - last;
        if (diff > 0) ans += diff;
        last = a;
    }
    cout << ans << endl;
    return 0;
}