#include <iostream>
#include <queue>
using namespace std;

int n, x;
priority_queue<int, vector<int>, greater<int>> pq;
int main() {
    cin >> n;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> x;
        pq.push(x);
    }
    while (pq.size() > 1) {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        a += b;
        ans += a;
        pq.push(a);
    }
    cout << ans << endl;
    return 0;
}