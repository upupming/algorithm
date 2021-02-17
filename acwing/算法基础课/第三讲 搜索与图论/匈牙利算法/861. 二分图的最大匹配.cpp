/*
每次都递归找一下增广路，如果可以找到，则在回溯时把增广路取反
把左部看做男生，右部看做女生，边看做可以建立恋爱关系，每个人只能有一个对象，我们的算法就是找到最多的恋爱关系
时间复杂度：O(NM)
*/
#include <cstring>
#include <iostream>
using namespace std;
// 注意只需要存从左部到右部的边即可
const int N = 510, M = 1e5 + 10;

int head[N], ver[M], Next[M], tot;
void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

// match[i] 表示右部的 i
int n1, n2, m, ans, match[N];
bool v[N];
bool dfs(int x) {
    for (int i = head[x], y; i; i = Next[i]) {
        if (!v[y = ver[i]]) {
            v[y] = 1;
            // 如果 y 正好没有男朋友；或者 y 有男朋友，但是 y 的男朋友 match[y] 可以换一个妹子的话；那么就把 y 的男朋友设置为 x
            if (!match[y] || dfs(match[y])) {
                match[y] = x;
                return true;
            }
        }
    }
    return false;
}
int main() {
    cin >> n1 >> n2 >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        add(u, v);
    }
    for (int i = 1; i <= n1; i++) {
        memset(v, 0, sizeof v);
        if (dfs(i)) ans++;
    }
    cout << ans << endl;
    return 0;
}