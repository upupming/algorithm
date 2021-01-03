/*
单调队列
最大值：
枚举右端点 i，越近、值又越大的元素是优先考虑的，入队时删去前面更小的数
1. 判断队头下标和 i 的距离是否超出 k，若超出则出队
2. 不断删除队尾元素，直到队尾对应的值大于 a[i]，然后把 a[i] 入队
3. 此时队头就以 i 为右端点时的窗口最大值
*/
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

int n, k, x;
deque<int> dqMax, dqMin;
vector<int> a, b, m;
int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> x;
        m.push_back(x);
        while (dqMax.size() && i - dqMax.front() >= k) dqMax.pop_front();
        while (dqMax.size() && m[dqMax.back()] <= x) dqMax.pop_back();
        dqMax.push_back(i);

        while (dqMin.size() && i - dqMin.front() >= k) dqMin.pop_front();
        while (dqMin.size() && m[dqMin.back()] >= x) dqMin.pop_back();
        dqMin.push_back(i);

        if (i >= k - 1) {
            a.push_back(m[dqMin.front()]);
            b.push_back(m[dqMax.front()]);
        }
    }
    for (int i = 0; i < n - k + 1; i++)
        cout << a[i] << " ";
    cout << endl;
    for (int i = 0; i < n - k + 1; i++)
        cout << b[i] << " ";
    cout << endl;
    return 0;
}