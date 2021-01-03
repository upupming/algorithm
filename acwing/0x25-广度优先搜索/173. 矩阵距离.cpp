/*
将所有的 1 作为起点进行广度优先搜索即可
*/
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 1010;
typedef pair<int, int> PII;

int n, m, a[N][N], d[N][N];
int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
queue<PII> q;
bool valid(PII &pii) {
    int x = pii.first, y = pii.second;
    return x >= 0 && x < n && y >= 0 && y < m;
}
int main() {
    cin >> n >> m;
    string s;
    memset(d, 0xff, sizeof(d));
    for (int i = 0; i < n; i++) {
        cin >> s;
        for (int j = 0; j < m; j++) {
            a[i][j] = s[j] - '0';
            if (a[i][j] == 1) {
                d[i][j] = 0;
                q.emplace(i, j);
            }
        }
    }

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            PII next = {cur.first + dx[i], cur.second + dy[i]};
            if (valid(next) && d[next.first][next.second] == -1) {
                q.push(next);
                d[next.first][next.second] = d[cur.first][cur.second] + 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}