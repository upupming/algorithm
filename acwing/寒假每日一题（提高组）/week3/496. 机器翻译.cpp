/*
队列 + 哈希（存储是否已经在内存中）
时间复杂度：O(N)
*/
#include <iostream>
#include <queue>
using namespace std;
const int N = 1100;

int m, n, a, v[N], ans;
queue<int> q;
int main() {
    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        cin >> a;
        if (!v[a]) {
            if (q.size() == m) v[q.front()] = 0, q.pop();
            q.push(a), ans++;
            v[a] = 1;
        }
    }
    cout << ans << endl;
    return 0;
}
