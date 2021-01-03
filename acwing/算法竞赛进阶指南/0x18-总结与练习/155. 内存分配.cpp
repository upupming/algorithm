/*
模拟题，细节比较多，要有足够的耐心
等待队列要存下来：(请求长度 M, 占用时间 P)
    queue
内存使用情况：（起始下标, 长度）
    线性扫描、删除、插入：set
小根堆：存放内存占用的 (释放时间 key, 内存起始下标)

算法流程：
for (T, M, P):
1. 释放所有释放时间 <= T 的内存，每次释放之后，判断等待队列的队头是否可以分配，可以分配就分配一下
2. 判断 (T, M, P) 是否可以满足，如果不可以，则插入等待队列
3. 结束后释放小根堆中的所有进程
*/
#include <climits>
#include <iostream>
#include <queue>
#include <set>
using namespace std;
typedef pair<int, int> PII;

// 等待队列要存下来：(请求长度 M, 占用时间 P)
queue<PII> wat;
// 内存使用情况：（起始下标, 长度）
set<PII> edtms;
// 小根堆：存放内存占用的 (释放时间 key, 内存起始下标)
priority_queue<PII, vector<PII>, greater<PII>> pq;
int n, t, m, p, cnt, endTime, idx;
// 返回可以分配的起始下标
int canAllocate(PII pir) {
    for (auto it = edtms.begin(); it != edtms.end();) {
        // 这一个结束时间到下一个开始时间之差
        int a = it->first + it->second;
        it++;
        if (it == edtms.end()) {
            break;
        }
        int b = it->first;
        if (b - a >= pir.first) return a;
    }
    return -1;
}
// 给进程分配空间，idx 是其实地址，startTime 是起始时间
void allocate(PII pir, int idx, int startTime) {
    int releaseTime = startTime + pir.second;
    edtms.insert({idx, pir.first});
    pq.push({releaseTime, idx});
}
// 判断等待队列的队头是否可以分配
void checkQueue() {
    while (wat.size() && ((idx = canAllocate(wat.front())) != -1)) {
        allocate(wat.front(), idx, endTime);
        wat.pop();
    }
}
// 释放结束时间点 <= time 的所有进程
void releaseAt(int time) {
    while (pq.size() && pq.top().first <= time) {
        int f = pq.top().first;
        // 坑点：可能有多个相同的结束时间的进程
        // 所有相同的删完之后才能去检查队列，不然不是最优的
        while (pq.size() && pq.top().first == f) {
            auto it = edtms.lower_bound({pq.top().second, 0});
            edtms.erase(it);
            pq.pop();
        }
        endTime = f;
        // 注意检查队列的时间点，多个同时结束都释放完毕
        checkQueue();
    }
}
int main() {
    cin >> n;

    // 插入哨兵，用于 canAllocate 判断左右端点的空闲区间
    // 用 -1 避免 lower_bound 找到并 erase，配对地后面用 1 保证 first + second = 0，用在 canAllocate 的变量 a 中
    edtms.insert({-1, 1}), edtms.insert({n, 0});

    while (cin >> t >> m >> p, t || m || p) {
        // 释放所有 <= T 的内存
        releaseAt(t);

        // 判断 (T, M, P) 是否可以满足，如果不可以，则插入等待队列
        auto ps = make_pair(m, p);
        if ((idx = canAllocate(ps)) != -1) {
            allocate(ps, idx, t);
        } else {
            wat.push(ps);
            cnt++;
        }
    }
    // 清空队列
    releaseAt(INT_MAX);

    cout << endTime << endl
         << cnt << endl;

    return 0;
}