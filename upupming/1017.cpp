#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int n, k, earlist = 8 * 3600, latest = 17 * 3600;
struct Customer {
    int arriving, proessing, finishing, waiting = 0, starting;
} customers[10005];

int cmp(Customer& a, Customer& b) { return a.arriving < b.arriving; }
struct cmp1 {
    bool operator()(int a, int b) {
        return customers[a].finishing > customers[b].finishing;
    }
};
priority_queue<int, vector<int>, cmp1> serving;

float solve() {
    sort(customers, customers + n, cmp);
    int totalWaiting = 0;
    int i = 0;
    for (; i < n; i++) {
        // cout << "i = " << i << ", arriving = " << customers[i].arriving << endl;
        if (customers[i].arriving >= latest) break;
        if (serving.size() == k) {
            int lastIndex = serving.top();
            serving.pop();
            customers[i].starting = max(customers[lastIndex].finishing, customers[i].arriving);
            // cout << "customer processing = " << customers[lastIndex].proessing << ", finishing = " << customers[lastIndex].finishing << " exit the queue" << endl;
        } else {
            // 为了不影响排序，对 earlist 的处理必须在排序之后进行
            customers[i].starting = max(earlist, customers[i].arriving);
        }
        // 在原来的基础上
        customers[i].waiting = customers[i].starting - customers[i].arriving;
        customers[i].finishing = customers[i].starting + ((customers[i].proessing > 60 * 60) ? 60 * 60 : customers[i].proessing);
        serving.push(i);
        totalWaiting += customers[i].waiting;
        // cout << "Waiting time of " << customers[i].proessing << " is " << customers[i].waiting << endl;
    }
    // 特殊情况！！！
    if (i == 0) return 0.0;
    return totalWaiting / 60.0 / i;
}

int main() {
    cin >> n >> k;
    int h, m, s;
    for (int i = 0; i < n; i++) {
        scanf("%d:%d:%d %d", &h, &m, &s, &customers[i].proessing);
        customers[i].proessing *= 60;
        int time = h * 60 * 60 + m * 60 + s;
        customers[i].arriving = time;
        // cout << "i = " << i << ", arriving = " << customers[i].arriving << endl;
    }
    printf("%.1f\n", solve());
    return 0;
}

/**

7 1
07:55:00 16
17:00:01 2
06:59:59 15
16:01:00 60
16:40:00 30
16:50:02 2
16:53:00 10

 */