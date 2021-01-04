/*
每次箱子移动后，人一定位于箱子之前处于的位置上
箱子刚刚移动后，箱子与人的位置打包成一个状态，记为 (x, y, dir)
(x, y): 表示箱子处于第 x 行第 y 列
dir: 一个 0 - 3 之间的整数值，指示人处于箱子旁边四个位置的哪一个
通过利用方向常数数组，人的位置可以表示为 (x - dx[dir], y - dy[dir])

使用数组 f_box[x][y][dir] 和 f_man[x][y][dir] 分别记录每个状态下箱子和人已经移动的步数
对于任意一个状态 (x, y, dir)，都可能有四个分支，代表箱子可能向4个方向移动
使用方向产常数数组，枚举方向 k=0~3，扩展到下一个状态就是 (x+dx[k], y+dy[k])，移动方式：
1. 箱子不动，人用尽量少的步数从起点 (x - dx[dir], y - dy[dir]) 移动到 (x+dx[k], y+dy[k])，并且途中不经过 (x, y)
2. 人沿着 k 方向推一次箱子，箱子移动到 (x+dx[k], y+dy[k])，人移动到 (x, y)
此后，将新状态 (x+dx[k], y+dy[k], k) 入队，并存储新状态对应的 f_box 与 f_man 的值

"双重" BFS 算法，每次箱子移动后，对箱子与旁边的人这个合体进行 BFS。而这个 BFS 在每一次状态拓展时，我们再用"对人进行另一个 BFS"求出人在两个位置之间移动的最少步数。

额外数组 pre 记录最终的每个 f_box 和 f_man 是从上一步哪个状态更新而来的，在求出最优解后向前逆推得到箱子的运动轨迹。
时间复杂度：O(N^2M^2)

std 程序好像跟书上的做法不太一样，抛弃了单调性，直接多个方案求一个 min 得到最终的解法了，这里采用 std 的写法
*/
#include <climits>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 25;
typedef pair<int, int> PII;

int n, m, t;
// 地图
char s[N][N];
struct P {
    // (x, y) 表示箱子位置，(px, py) 表示人的位置
    int x, y, px, py;
    // 到达这状态所需要的操作记录
    string ans;
};
int d[2][4] = {
    {-1, 1, 0, 0},
    {0, 0, -1, 1},
};
// 注意题目的顺序要求，因为步数相同的情况下最优解不会被替换，枚举的时候需要按照题目要求的顺序来
char A[4] = {'N', 'S', 'W', 'E'};
char a[4] = {'n', 's', 'w', 'e'};

bool valid(int x, int y) {
    return x > 0 && x <= n && y > 0 && y <= m && s[x][y] != '#';
}
void out(P p) {
    cout << p.x << " " << p.y << " " << p.px << " " << p.py << " " << p.ans << endl;
}
// 人的行走路线暂存
string tmp;
// 搜索人
// 如果人无法从 src.px/py 所在的位置到达 px/py，则方案不可行
// 注意人在走的过程中不能途经箱子 src.x/y
bool bfs2(P src, int px, int py) {
    src.ans = "";
    tmp = "";
    queue<P> q;
    q.push(src);
    bool v[N][N];
    memset(v, 0, sizeof(v));
    while (q.size()) {
        P now = q.front(), nxt;
        q.pop();
        // 如果到达目标点
        if (now.px == px && now.py == py) {
            tmp = now.ans;
            return 1;
        }
        for (int i = 0; i < 4; i++) {
            nxt = now;
            nxt.px = now.px + d[0][i];
            nxt.py = now.py + d[1][i];
            if (!valid(nxt.px, nxt.py)) continue;
            // 不能途经箱子
            if (nxt.px == src.x && nxt.py == src.y) continue;
            if (v[nxt.px][nxt.py]) continue;
            v[nxt.px][nxt.py] = 1;
            nxt.ans = now.ans + a[i];
            q.push(nxt);
        }
    }
    return 0;
}
// 搜索箱子
string bfs1() {
    P st;
    st.ans = "";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // 箱子位置
            if (s[i][j] == 'B') {
                st.x = i, st.y = j;
                s[i][j] = '.';
            } else if (s[i][j] == 'S') {
                st.px = i, st.py = j;
                s[i][j] = '.';
            }
        }
    }
    queue<P> q;
    q.push(st);
    bool v[N][N][4];
    memset(v, 0, sizeof v);
    string ans = "Impossible.";
    // 箱子和人走的步数记录
    int boxCnt = INT_MAX, manCnt = INT_MAX;
    while (q.size()) {
        P now = q.front(), nxt;
        q.pop();
        // 到达终点了
        if (s[now.x][now.y] == 'T') {
            int nowBoxCnt = 0, nowManCnt = 0;
            for (int i = 0; i < now.ans.length(); i++) {
                if (now.ans[i] >= 'A' && now.ans[i] <= 'Z')
                    nowBoxCnt++;
                else
                    nowManCnt++;
            }
            if (nowBoxCnt < boxCnt ||
                (nowBoxCnt == boxCnt && nowManCnt < manCnt)) {
                ans = now.ans;
                boxCnt = nowBoxCnt;
                manCnt = nowManCnt;
            }
            continue;
        }

        // 拓展 4 个方向
        for (int i = 0; i < 4; i++) {
            nxt = now;
            // 箱子的下一个位置
            nxt.x = now.x + d[0][i];
            nxt.y = now.y + d[1][i];
            if (!valid(nxt.x, nxt.y)) continue;
            if (v[nxt.x][nxt.y][i]) continue;

            // 在推箱子之前，人必须到的位置
            int px, py;
            px = now.x - d[0][i];
            py = now.y - d[1][i];
            // 如果人无法从 now.px/py 所在的位置到达 px/y，则方案不可行
            // 注意人在走的过程中不能途经箱子 now.x/y
            if (!bfs2(now, px, py)) {
                continue;
            }

            v[nxt.x][nxt.y][i] = 1;
            nxt.ans = now.ans + tmp;
            nxt.ans += A[i];
            // 移动之后，人到了原来箱子的位置上
            nxt.px = now.x, nxt.py = now.y;
            q.push(nxt);
        }
    }
    return ans;
}
int main() {
    while (cin >> n >> m && n && m) {
        for (int i = 1; i <= n; i++) {
            cin >> (s[i] + 1);
        }
        cout << "Maze #" << ++t << endl
             << bfs1() << endl
             << endl;
    }
    return 0;
}
