/*
双向 BFS
A 和 B 都变成 C，所需步数之和
A -> C <- B
问题：如何处理字符串的替换？

步数最多为 10，每次变化数量最多为 K
单向 BFS 时间复杂度：O(K^10)
双向 BFS 时间复杂度：O(2K^5)
K = LN，其中 L 为字符串长度，N 为替换规则的数量
*/
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;
const int N = 6;

int n;
string A, B, a[N], b[N];
// 从初始状态到达对应字符串需要拓展的距离
unordered_map<string, int> da, db;
int bfs() {
    queue<string> qa, qb;
    qa.push(A), qb.push(B);
    da[A] = db[B] = 0;

    // 只要 qa 为空，就说明 A 所有可能到达的状态都搜过了
    // 如果还不能到 B 的话，说明已经是无解的了
    while (qa.size() && qb.size()) {
        // 优化：优先拓展较小的队列（不加这个会 TLE）
        if (qa.size() < qb.size()) {
            // 这一层的数量为 s，主需要拓展一层
            // 可以参考噩梦这一题，双向 BFS 都是一层一层拓展的
            int s = qa.size();
            for (int i = 0; i < s; i++) {
                auto now = qa.front();
                qa.pop();

                // 枚举所有可能的变化情况
                // 1. 枚举所有起点
                for (int i = 0; i < now.length(); i++) {
                    // 2. 枚举所有可能的变化方案
                    for (int j = 0; j < n; j++) {
                        // 如果匹配上某个规则的 Ai
                        if (now.substr(i, a[j].length()) == a[j]) {
                            // 替换为对应的 Bi
                            string next = now.substr(0, i) + b[j] + now.substr(i + a[j].length());

                            if (da.count(next)) continue;
                            da[next] = da[now] + 1;
                            qa.push(next);
                            if (db.count(next)) return da[next] + db[next];
                        }
                    }
                }
            }
        } else {
            int s = qb.size();
            for (int i = 0; i < s; i++) {
                auto now = qb.front();
                qb.pop();

                // 枚举所有可能的变化情况
                // 1. 枚举所有起点
                for (int i = 0; i < now.length(); i++) {
                    // 2. 枚举所有可能的变化方案
                    for (int j = 0; j < n; j++) {
                        // 如果匹配上某个规则的 Bi
                        if (now.substr(i, b[j].length()) == b[j]) {
                            // 替换为对应的 Ai
                            string next = now.substr(0, i) + a[j] + now.substr(i + b[j].length());

                            if (db.count(next)) continue;
                            db[next] = db[now] + 1;
                            qb.push(next);
                            if (da.count(next)) return da[next] + db[next];
                        }
                    }
                }
            }
        }
    }

    // 最多步数为 10，11 表示无解
    return 11;
}
int main() {
    cin >> A >> B;
    while (cin >> a[n] >> b[n]) n++;

    int step = bfs();
    if (step > 10)
        puts("NO ANSWER!");
    else
        cout << step << endl;

    return 0;
}