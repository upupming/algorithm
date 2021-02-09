/*
对于每一个星群，生成一个 hash 值，如果星群一样 ，hash 值一定一样；如果星群不一样，hash 值不一样的概率很大很大；可以直接比较 hash 值来认为是否是一个星群
搜索星群的时候，使用 BFS 或者 DFS 均可
因为是 8 领域，直接两层循环来找邻居即可
*/
#include <cmath>
#include <iostream>
using namespace std;
typedef pair<int, int> PII;
const int N = 110;
const double eps = 1e-6;

int n, m, top, id;
char g[N][N];
// 存放当前星群的所有坐标
PII q[N * N];
void dfs(int a, int b) {
    q[top++] = {a, b};
    // 相当于标记为已经访问
    g[a][b] = '0';
    for (int x = a - 1; x <= a + 1; x++) {
        for (int y = b - 1; y <= b + 1; y++) {
            if (x == a && y == b) continue;
            if (x >= 0 && x < n && y >= 0 && y < m && g[x][y] == '1')
                dfs(x, y);
        }
    }
}
double dist(PII a, PII b) {
    int d1 = a.first - b.first, d2 = a.second - b.second;
    return sqrt(d1 * d1 + d2 * d2);
}
// hash 值算法：两两之间的欧拉距离之和，要开平方是为了尽量减少冲突
double get_hash() {
    double sum = 0;
    for (int i = 0; i < top; i++) {
        for (int j = i + 1; j < top; j++) {
            sum += dist(q[i], q[j]);
        }
    }
    return sum;
}
char get_id(double key) {
    // hash[i] 表示第 i 个不同星群的 hash 值
    static double hash[30];
    for (int i = 0; i < id; i++) {
        if (fabs(hash[i] - key) < eps) {
            return i + 'a';
        }
    }
    hash[id++] = key;
    return id - 1 + 'a';
}
int main() {
    cin >> m >> n;
    for (int i = 0; i < n; i++) cin >> g[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '1') {
                top = 0;
                dfs(i, j);
                // 计算 hash，然后得到已有 id 或者创建新的 id
                char c = get_id(get_hash());
                // 全部用 id 进行标记
                for (int k = 0; k < top; k++) {
                    g[q[k].first][q[k].second] = c;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) cout << g[i] << endl;
    return 0;
}