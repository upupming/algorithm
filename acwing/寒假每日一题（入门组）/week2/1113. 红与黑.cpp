#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 30;
typedef pair<int, int> PII;

int w, h, ans, v[N][N];
int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
char s[N][N];
PII start;
bool valid(int x, int y) {
    return x >= 0 && x < h && y >= 0 && y < w && s[x][y] == '.';
}
int main() {
    while (cin >> w >> h && (w || h)) {
        memset(v, 0, sizeof(v)), ans = 0;
        for (int i = 0; i < h; i++) {
            cin >> s[i];
            for (int j = 0; j < w; j++) {
                if (s[i][j] == '@') start = {i, j};
            }
        }
        queue<PII> q;
        ans++;
        q.push(start);
        while (q.size()) {
            auto now = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int x = now.first + dx[i];
                int y = now.second + dy[i];
                if (!valid(x, y) || v[x][y]) continue;
                v[x][y] = 1;
                ans++;
                q.push({x, y});
            }
        }
        cout << ans << endl;
    }
    return 0;
}