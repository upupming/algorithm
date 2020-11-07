#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**

1. build a tree, mark all leaves & leaf height
2. leaf height -> # of paint
3. average

special cases: only 1 node

 */

int t, n, a, b, tree[500010], p1[500010], p2[500010];
bool isLeaf[500010];
vector<int> children[500010];

void cntNode(int i, int *p1, int *p2, int depth, int per1, int per2) {
    if (depth % per1 == 0) p1[i]++;
    if (depth % per2 == 0) p2[i]++;
    if (i == 1) return;
    cntNode(tree[i - 2], p1, p2, depth + 1, per1, per2);
}

double getAns() {
    double ans = 0;
    // cout << "nLeaves:" << nLeaves << endl;
    for (int i = 1; i <= n; i++) {
        // cout << "i: " << i << ", p1[i]: " << p1[i] << ", p2[i]: " << p2[i] << endl;
        double probability1 = (double)p1[i] / n;
        double probability2 = (double)p2[i] / n;
        ans += (1 - (1 - probability1) * (1 - probability2));
    }

    return ans;
}

double solve() {
    // 以节点 i 作为终止节点的时候，能够涂上颜色的节点
    for (int i = 1; i <= n; i++) {
        cntNode(i, p1, p2, 0, a, b);
    }

    return getAns();
}

void dfs(int i, vector<int> &path_taken) {
    // 以 i 作为终止点
    p1[i]++, p2[i]++;

    // cout << "current i: " << i << endl;
    path_taken.push_back(i);
    // 以 i 作为中间点
    for (auto j : children[i]) {
        dfs(j, path_taken);
    }
    path_taken.erase(path_taken.end() - 1);

    // 关键优化：如果有对应的父节点，相隔 a 或者 b 的父亲节点要加上当前的结果数
    int n = path_taken.size();
    if (n - a >= 0)
        p1[path_taken[n - a]] += p1[i];
    if (n - b >= 0)
        p2[path_taken[n - b]] += p2[i];
}

double solve1() {
    // 关键优化：从 1 号 root 节点开始进行 DFS，只需要线性时间就可以遍历完
    vector<int> path_taken{};
    dfs(1, path_taken);

    return getAns();
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> a >> b;
        for (int i = 0; i <= n; i++) {
            isLeaf[i] = true;
            p1[i] = p2[i] = 0;
            children[i].clear();
        }
        for (int i = 0; i < n - 1; i++) {
            cin >> tree[i];
            isLeaf[tree[i]] = false;
            children[tree[i]].push_back(i + 2);
        }

        printf("Case #%d: %lf\n", i, solve1());
    }
    return 0;
}