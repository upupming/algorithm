/*
对顶堆，最大堆堆顶小于最小堆的堆顶
ADD: 根据数的大小情况，放入最小堆或者最大堆
    调整大小，直至最大堆中有 i 个元素，最大堆堆顶就是所求
GET: 返回最大堆堆顶元素，然后 i++，调整大小直至最大堆中有 i 个元素
*/
#include <iostream>
#include <queue>
using namespace std;
const int N = 3e4 + 10;

priority_queue<int> maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap;
int a[N], u[N], m, n, cur = 1;
void adjust() {
    // 调整大小，直到最大堆刚刚好 cur 个元素
    while (maxHeap.size() > cur) {
        minHeap.push(maxHeap.top());
        maxHeap.pop();
    }
    // 中间状态的时候（i + 1 != u[j]）要避免 minHeap 调整成空
    while (maxHeap.size() < cur && minHeap.size()) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
    }

    // cout << maxHeap.size() << " " << minHeap.size() << " " << cur << endl;
}
int main() {
    cin >> m >> n;
    for (int i = 0; i < m; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> u[i];
    for (int i = 0, j = 0; i < m; i++) {
        // 第一个元素放入最大堆
        if (i == 0) {
            maxHeap.push(a[i]);
        } else {
            if (a[i] > maxHeap.top()) {
                minHeap.push(a[i]);
            } else {
                maxHeap.push(a[i]);
                adjust();
            }
        }

        while (i + 1 == u[j]) {
            cout << maxHeap.top() << endl;
            // 注意题目要求「GET：使i增加1」，对应 cur++
            cur++, j++;
            adjust();
        }
    }
    return 0;
}