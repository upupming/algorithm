/*
vector 不断插入，自己维护有序性即可，同时也支持随机存取，复杂度 m log m
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int p, m, no;
vector<int> a;
priority_queue<int> maxHeap, maxEmpty;
priority_queue<int, vector<int>, greater<int>> minHeap, minEmpty;

// 对顶堆
void solve1() {
    maxHeap = maxEmpty, minHeap = minEmpty;
    int x, cnt = 0;
    for (int i = 1; i <= m; i++) {
        cin >> x;
        // 小根堆多存一个
        if (i == 1)
            minHeap.push(x);
        else {
            if (x < minHeap.top()) {
                maxHeap.push(x);
                while (maxHeap.size() > minHeap.size()) {
                    int y = maxHeap.top();
                    minHeap.push(y), maxHeap.pop();
                }
            } else {
                minHeap.push(x);
                while (minHeap.size() > maxHeap.size() + 1) {
                    int y = minHeap.top();
                    maxHeap.push(y), minHeap.pop();
                }
            }
        }
        if (i % 2) {
            if (cnt % 10 == 0 && cnt > 0)
                cout << endl;
            else if (i > 1)
                cout << " ";
            cout << minHeap.top();
            cnt++;
        }
    }
    cout << endl;
}

// insert + lower_bound
void solve() {
    a.clear();
    int x, cnt = 0;
    for (int i = 1; i <= m; i++) {
        cin >> x;
        // 插入的同时保持有序性
        a.insert(lower_bound(a.begin(), a.end(), x), x);

        if (i % 2) {
            if (cnt % 10 == 0 && cnt > 0)
                cout << endl;
            else if (i > 1)
                cout << " ";
            cout << a[i / 2];
            cnt++;
        }
    }
    cout << endl;
}

int main() {
    cin >> p;
    while (p--) {
        cin >> no >> m;
        cout << no << " " << (m + 1) / 2 << endl;
        solve1();
    }
    return 0;
}