/*
k 叉 Huffman 数，需要满足 n = a * (k - 1) + 1，不够的话需要补权值为 0 的节点，构造的时候权值为 0 的节点自然地会被放在最下面
越早合并的节点，最后越深，如果有多个相同候选，优先选深度小的
*/
#include <iostream>
#include <queue>
using namespace std;

typedef long long ll;
// 1. 权值小 2. 高度低
typedef pair<ll, int> PLI;

priority_queue<PLI, vector<PLI>, greater<PLI>> pq;
ll n, k, x;
int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> x;
        pq.emplace(x, 0);
    }
    while ((n - 1) % (k - 1)) pq.emplace(0, 0), n++;
    ll ans = 0;
    while (pq.size() >= k) {
        ll weight = 0;
        int depth = -1;
        // 合并 k 个节点
        for (int i = 0; i < k; i++) {
            auto q = pq.top();
            pq.pop();
            weight += q.first;
            depth = max(depth, q.second);
        }
        pq.emplace(weight, depth + 1);
        ans += weight;
    }
    cout << ans << endl
         << pq.top().second << endl;
    return 0;
}