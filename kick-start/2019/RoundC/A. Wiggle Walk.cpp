/*
必须在 O(1) 时间内完成一次移动
L 数组表示某个点最左能到达的已访问过的地方，R, U, D 同理，来缩短时间，但是维护这个信息本身又无法通过 O(1) 完成

发现连续的 EW 可以任意调换位置
例如 EEW 和 WEE 等价，只是 EEW 最后的终点一定在左边偏移 1 个位置的地方，因此我们可以直接将 EE 这部分染色，然后将 W 这部分染色，最后直接将坐标位置更新为计算到的地方
这样平均下来每个操作都是 O(1) 的了
*/
#include <cstring>
#include <iostream>
#include <unordered_map>
using namespace std;
const int N = 5e4 + 10;

int sr, sc, t, n, r, c;
unordered_map<int, unordered_map<int, int>> g;
string cmd;

int getType(char ch) {
    if (ch == 'W' || ch == 'E') return 1;
    if (ch == 'N' || ch == 'S') return 2;
    return -1;
}
void solve() {
    g.clear();
    g[sr][sc] = 1;
    for (int i = 0, j; i < n;) {
        j = i;
        int type = getType(cmd[i]);
        while (j < n && getType(cmd[j]) == type) j++;
        int leftMax = 0, rightMax = 0;
        for (int k = i; k < j; k++) {
            if (cmd[k] == 'W' || cmd[k] == 'N')
                leftMax++;
            else
                rightMax++;
        }
        if (type == 1) {
            int x = sr, y = sc;
            // 向左走 leftMax 步
            for (int k = 0; k < leftMax; k++) {
                while (g[x][y]) y--;
                g[x][y] = 1;
            }
            int x1 = sr, y1 = sc;
            // 向右走 rightMax 步
            for (int k = 0; k < rightMax; k++) {
                while (g[x1][y1]) y1++;
                g[x1][y1] = 1;
            }
            if (cmd[j - 1] == 'W')
                sr = x, sc = y;
            else
                sr = x1, sc = y1;
        } else {
            int x = sr, y = sc;
            // 向上走 leftMax 步
            for (int k = 0; k < leftMax; k++) {
                while (g[x][y]) x--;
                g[x][y] = 1;
            }
            int x1 = sr, y1 = sc;
            // 向下走 rightMax 步
            for (int k = 0; k < rightMax; k++) {
                while (g[x1][y1]) x1++;
                g[x1][y1] = 1;
            }
            if (cmd[j - 1] == 'N')
                sr = x, sc = y;
            else
                sr = x1, sc = y1;
        }
        i = j;
    }
}
int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> r >> c >> sr >> sc >> cmd;
        solve();
        printf("Case #%d: %d %d\n", i, sr, sc);
    }
    return 0;
}
