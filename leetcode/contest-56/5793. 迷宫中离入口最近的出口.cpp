#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
struct P {
    int x, y, steps;
};
int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
class Solution {
   public:
    int m, n;
    vector<vector<char>> maze;
    bool isExit(const P& p) {
        return (p.steps >= 1 && (p.x == 0 || p.x == m - 1 || p.y == 0 || p.y == n - 1));
    }
    bool valid(int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n && maze[x][y] != '+';
    }
    int nearestExit(vector<vector<char>>& _maze, vector<int>& entrance) {
        maze = _maze;
        m = maze.size(), n = maze[0].size();
        vector<vector<bool>> v(m, vector<bool>(n, false));
        queue<P> q;
        q.push({entrance[0], entrance[1], 0});
        v[entrance[0]][entrance[1]] = 1;
        while (q.size()) {
            auto now = q.front();
            q.pop();
            if (isExit(now)) {
                return now.steps;
            }
            for (int k = 0; k < 4; k++) {
                int x = now.x + dx[k], y = now.y + dy[k];
                if (valid(x, y) && !v[x][y]) {
                    // cout << x << " " << y << " " << now.steps + 1 << endl;
                    q.push({x, y, now.steps + 1});
                    v[x][y] = 1;
                }
            }
        }
        return -1;
    }
};
