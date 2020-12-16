/*
动手之前一定要确保思路是正确的，最好自己多构造一些测试的 case

每次只考虑两行，两行求完前 N 小和之后再和下面继续重复取。
最小堆维护第 k 小和的候选集即可，每次确定一个第 k 最小和为 A[i]+B[j]，就需要将 A[i+1]+B[j] 和 A[i]+B[j+1] 加入候选集，避免重复，需要加一个标志变量 last 表示之前移动的指针是不是 j，如果是 j，后续只能移动 j
注意堆元素按照 A[i] + B[j] 进行排序

y总的思路更为简单，直接将和存入堆，只有较小的和出堆，后面较大的和才能入堆
*/
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
const int M = 1010, N = 2010;

// k 表示当前在对第 k 和 k + 1 行求前 N 小和
int m, n, a[M][N], t, b[N], k;
struct Node {
    int i, j, last;
    // 注意维护的是最小堆
    bool operator<(const Node& b) const {
        return a[k][i] + a[k + 1][j] > a[k][b.i] + a[k + 1][b.j];
    }
};
int main() {
    cin >> t;
    while (t--) {
        cin >> m >> n;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
            }
            sort(a[i], a[i] + n);
        }
        for (int i = 0; i < m - 1; i++) {
            k = i;
            // 求 a[i] 和 a[i+1] 之间的前 N 小和
            priority_queue<Node> pq;
            Node node;
            node.i = node.j = 0, node.last = 0;
            pq.push(node);
            for (int j = 0; j < n; j++) {
                auto tmp = pq.top();
                pq.pop();
                // cout << tmp.i << " " << tmp.j << " " << tmp.last << endl;
                b[j] = a[i][tmp.i] + a[i + 1][tmp.j];
                Node x;
                x.i = tmp.i, x.j = tmp.j + 1, x.last = 1;
                pq.push(x);
                if (!tmp.last) {
                    x.i = tmp.i + 1, x.j = tmp.j, x.last = 0;
                    pq.push(x);
                }
            }
            sort(b, b + n);
            // 复制到 a[i+1] 便于下一轮操作
            for (int j = 0; j < n; j++) a[i + 1][j] = b[j];
        }
        for (int j = 0; j < n; j++)
            cout << a[m - 1][j] << " ";
        cout << endl;
    }
    return 0;
}