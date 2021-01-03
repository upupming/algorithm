/*
维护一个最小堆，来一个新的商品，如果当前堆中商品个数等于 d_i，那么要放进去就必须拿出一个来，比较一下堆顶看值不值得放进去（p_i 大于堆顶的 p）即可。

y 总的思路更简单，不管怎样，先加进去，如果加进去的这个过期时间小于堆大小，然后 pop 一个出来，pop 出来的就是最小的了
*/
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 10010;

int n, tot;
// 二叉堆模板，书上下标从 1 开始索引，这个例子是最小堆
pair<int, int> heap[N], d_p[N];
// 向上调整
void up(int p) {
    while (p > 1) {
        if (heap[p] < heap[p / 2]) {
            swap(heap[p], heap[p / 2]);
            p /= 2;
        } else
            break;
    }
}
void insert(pair<int, int> val) {
    heap[++tot] = val;
    up(tot);
}
// 向下调整
void down(int p) {
    // 左子节点
    int s = 2 * p;
    while (s <= tot) {
        // 左右子节点中取较小者
        if (s < tot && heap[s] > heap[s + 1]) s++;
        if (heap[p] > heap[s]) {
            swap(heap[p], heap[s]);
            p = s, s = 2 * p;
        } else
            break;
    }
}
int main() {
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            cin >> d_p[i].second >> d_p[i].first;
        }
        // 按照 d 从小到大排序
        sort(d_p, d_p + n);

        tot = 0;
        // 构建二叉堆
        for (int i = 0; i < n; i++) {
            int d = d_p[i].first, p = d_p[i].second;
            if (tot < d) {
                insert({p, d});
            } else if (tot == d) {
                if (heap[1].first < p) {
                    heap[1] = {p, d};
                    down(1);
                }
            } else
                break;
        }
        int sum = 0;
        // 求和
        for (int i = 1; i <= tot; i++) {
            sum += heap[i].first;
        }
        cout << sum << endl;
    }
}