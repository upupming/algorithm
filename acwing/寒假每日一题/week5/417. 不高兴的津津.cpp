#include <iostream>
#include <queue>
using namespace std;
typedef pair<int, int> PII;

int n = 7, a, b;
priority_queue<PII> pq;
int main() {
    for (int i = 1; i <= n; i++) {
        cin >> a >> b;
        if (a + b > 8) {
            pq.emplace(a + b, -i);
        }
    }
    if (pq.size())
        cout << -pq.top().second << endl;
    else
        cout << 0 << endl;
    return 0;
}