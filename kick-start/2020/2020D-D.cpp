#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

// ATTENTION!!!: 提交前一定要注释这里
// #define DEBUG

// ft[100010][17] 过不了测试
// 因为 log_2(100000) = 16.6, m = ceil(16.6) = 17
// ft[?][17] 访问的时候会拿到错误的值，从而造成 WA
// 而且这个在 Google 的机器上越界访问居然不是 RE
// 足以见得 unspecified behavior 是多么的神奇
// 看别人的代码，一般用 20 足够了
// https://codeforces.com/blog/entry/80040#comment-662229
// 2 ^ 19 = 524288

int t, n, q, d[100010], s, k, lft[100010], rht[100010], tree[100010][3], ft[100010][20], m, size[100010];

void print(int *a) {
    cout << endl
         << "print" << endl;
    for (int i = 0; i < n - 1; i++) {
        cout << " " << a[i];
    }
    cout << endl;
}

void printTree(int i) {
    if (i == -1) return;
    printTree(tree[i][1]);
    cout << " " << i;
    printTree(tree[i][2]);
}
void printTreePost(int i) {
    if (i == -1) return;
    printTreePost(tree[i][1]);
    printTreePost(tree[i][2]);
    cout << " " << i;
}

// O(n) with 单调栈
void calLeftAndRight() {
    stack<int> s, t;
    for (int i = 0; i < n - 1; i++) {
        while (!s.empty() && d[s.top()] < d[i]) s.pop();
        if (s.empty())
            s.push(i), lft[i] = -1;
        else
            lft[i] = s.top(), s.push(i);
    }
    for (int i = n - 2; i >= 0; i--) {
        while (!t.empty() && d[t.top()] < d[i]) t.pop();
        if (t.empty())
            t.push(i), rht[i] = -1;
        else
            rht[i] = t.top(), t.push(i);
    }

    // print(lft);
    // print(rht);
}

// O(n) to assign parent for each node
void constructBinarySearchTree() {
    for (int i = 0; i < n - 1; i++) {
        if ((lft[i] != -1 && rht[i] != -1 && d[lft[i]] < d[rht[i]]) || (lft[i] != -1 && rht[i] == -1))
            // tree[i][0] 表示 i 的父节点，tree[i][1] 表示 i 的左儿子，tree[i][2] 表示 i 的右儿子
            tree[i][0] = lft[i], tree[lft[i]][2] = i;
        else if ((lft[i] != -1 && rht[i] != -1 && d[lft[i]] > d[rht[i]]) || (lft[i] == -1 && rht[i] != -1))
            tree[i][0] = rht[i], tree[rht[i]][1] = i;
    }

    // printTree(5);
    // cout << endl;
    // printTreePost(5);
    // cout << endl;
}

// O(long n) to find the root
int findRoot(int u) {
    if (tree[u][0] == -1) return u;
    return findRoot(tree[u][0]);
}

// O(n log n) to precompute subtree size & father table (a sparse table)
// return size of the tree
int dfs(int u, int parent) {
    if (u == -1) return 0;

    ft[u][0] = parent;
    for (int i = 1; i <= m; i++) {
        ft[u][i] = ft[ft[u][i - 1]][i - 1];
    }
    size[u] = dfs(tree[u][1], u) + dfs(tree[u][2], u) + 1;
    return size[u];
}

void solve() {
    calLeftAndRight();
    constructBinarySearchTree();
    int root = findRoot(0);
    // cout << "root: " << root << endl;
    fill_n(&ft[0][0], sizeof(ft) / sizeof(ft[0][0]), root);
    dfs(root, root);
}

// O(log n)
int getAns() {
    // the first door will be unlocked: x
    int x1 = s - 2, x2 = s - 1, x;

    if (x1 >= 0 && x2 <= n - 2) {
        if (d[x1] < d[x2])
            x = x1;
        else
            x = x2;
    } else {
        if (x1 < 0)
            x = x2;
        else
            x = x1;
    }

    // 第 1 步已经走了，所以还剩下 k - 1 步
    if (size[x] >= k - 1)
        if (x == x1)
            return s - (k - 1);
        else
            return s + (k - 1);
    else {
        // find node Y which is the first node on path from X to root such that size[Y] ≥ K
        // O(log n)
        int y = x;
        for (int kIndex = m; kIndex >= 0; kIndex--) {
            if (size[ft[y][kIndex]] < k - 1) {
                y = ft[y][kIndex];
            }
        }
        y = ft[y][0];
        // cout << endl;
        // cout << x << ", " << y << ", " << size[y] << endl;

        if (x < y) {
            // cout
            //     << "case 1" << endl;
            return y + k - size[tree[y][1]];
        } else {
            // cout
            //     << "case 2" << endl;
            return y + 1 - (k - size[tree[y][2]]) + 2;
        }
    }
}

int main() {
#ifdef DEBUG
    ifstream cin("input.in");
#endif

    cin >> t;
    for (int i = 1; i <= t; i++) {
        fill_n(&tree[0][0], sizeof(tree) / sizeof(tree[0][0]), -1);

        cin >> n >> q;
        m = (int)ceil(log2(n));

        for (int i = 0; i < n - 1; i++) cin >> d[i];

        solve();

        printf("Case #%d: ", i);
        for (int i = 0; i < q; i++) {
            cin >> s >> k;
            if (i != 0) printf(" ");
            printf("%d", getAns());
        }

        printf("\n");
    }
    return 0;
}