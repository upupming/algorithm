// 三维 M * N * L 的立方体，从 1 元素开始进行 dfs 遍历，体积大于 T 则计入总量
// 结束条件：1. 周围全是 0；2. 之前已经遍历过

#include <iostream>
#include <queue>

using namespace std;

int m, n, l, t, a[1300][140][100];
bool visited[1300][140][100];

struct pos {
    int x, y, z;
};

// 使用 dfs 会造成栈溢出，C++ max stack size = 1MB
int dfs(int mm, int nn, int ll) {
    if (mm < 0 || mm >= m || nn < 0 || nn >= n || ll < 0 || ll >= l) return 0;
    
    if (a[mm][nn][ll] == 0 || visited[mm][nn][ll]) return 0;
    
    visited[mm][nn][ll] = true;
    return 1 + dfs(mm-1, nn, ll) + 
        dfs(mm+1, nn, ll) + 
        dfs(mm, nn-1, ll) + 
        dfs(mm, nn+1, ll) +
        dfs(mm, nn, ll-1) + 
        dfs(mm, nn, ll+1);
}

void inQueue(int mm, int nn, int ll, queue<pos>& q) {
    if (mm < 0 || mm >= m || nn < 0 || nn >= n || ll < 0 || ll >= l) return;
    
    if (a[mm][nn][ll] == 0 || visited[mm][nn][ll]) return;
    
    visited[mm][nn][ll] = true;
    pos tmp;
    tmp.x = mm, tmp.y = nn, tmp.z = ll;
    q.push(tmp);
}
int bfs(int mm, int nn, int ll) {
    queue<pos> q;
    visited[mm][nn][ll] = true;
    pos tmp;
    tmp.x = mm, tmp.y = nn, tmp.z = ll;
    q.push(tmp);
    int cnt = 0;
    while(!q.empty()) {
        pos top = q.front(); q.pop();
        cnt++;
        inQueue(top.x-1, top.y, top.z, q);
        inQueue(top.x+1, top.y, top.z, q); 
        inQueue(top.x, top.y-1, top.z, q);
        inQueue(top.x, top.y+1, top.z, q);
        inQueue(top.x, top.y, top.z-1, q); 
        inQueue(top.x, top.y, top.z+1, q);
    }
    return cnt;
}

int main() {
    scanf("%d %d %d %d", &m, &n, &l, &t);
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                scanf("%d", &a[j][k][i]);
            }
        }
    }
    int total = 0;
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                if (!visited[j][k][i] && a[j][k][i] == 1) {
                    int v = bfs(j, k, i);
                    if (v >= t) total += v;
                }
            }
        }
    }
    printf("%d\n", total);
    return 0;
}