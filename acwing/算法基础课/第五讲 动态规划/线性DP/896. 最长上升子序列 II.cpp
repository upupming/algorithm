/*
朴素 dp 可以进一步优化
如果结尾更小，单调子串长度还更大，后面肯定是更优先选这个数，可以舍弃其他数
另一个性质是：随着单调子串长度的增加，结尾一定是单调不减的，可用反证法证明
因此，可以用 q[i] 表示长度为 i 的单调子串的结尾最小值，q[i] 具有单调性，因此可以二分

例子：
n: 10
i: 0      1  2  3
a: -5    -1  8 -4 3 -2 -5 -6 2 -6
q: 2e-9
q: 2e-9  -5 -1  8
q: 2e-9  -5 -4  8

可参考：https://www.acwing.com/solution/content/6941/
...
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;

int n, a[N], q[N];
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    q[0] = -2e9;
    int len = 0;
    for (int i = 0; i < n; i++) {
        // 找到最大的长度满足 q[?] < a[i]，也就是说 q[?] >= a[i]，最后可以用 a[i] 去更新 q[?]
        int l = 0, r = len;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (q[mid] < a[i])
                l = mid;
            else
                r = mid - 1;
        }
        // 之前的长度是 r，增加一个元素 a[i] 变成 r + 1
        len = max(len, r + 1);
        // 由于二分搜索的性质，q[r+1] >= a[i]，这个更新一定会将其更新为当前长度为 r + 1 子序列的最小结尾值
        q[r + 1] = a[i];
        // cout << r + 1 << " " << q[r + 1] << endl;
    }
    cout << len << endl;
    return 0;
}