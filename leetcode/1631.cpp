
// https://leetcode.com/contest/weekly-contest-212/problems/path-with-minimum-effort/
#include <bits/stdc++.h>
using namespace std;

// Left, Right Top, Bottom four directions
int delta[4][2] = {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0}};

class Solution {
   public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int rows = heights.size(), cols = heights[0].size();
        int key[110][110], parent_i[110][110], parent_j[110][110];
        bool visited[110][110];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                key[i][j] = INT_MAX;
                visited[i][j] = false;
            }
        }
        // source: 0, 0; destination: rows - 1, cols - 1
        key[0][0] = 0;
        while (true) {
            // Extract minimun
            int ui = -1, uj = -1, minKey = INT_MAX;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (!visited[i][j] && key[i][j] < minKey) {
                        ui = i;
                        uj = j;
                        minKey = key[i][j];
                    }
                }
            }
            if (ui == -1) break;

            visited[ui][uj] = true;
            for (auto d : delta) {
                int i = ui + d[0], j = uj + d[1];
                if (i >= 0 && i < rows && j >= 0 && j < cols && !visited[i][j]) {
                    int distance = abs(heights[i][j] - heights[ui][uj]);
                    if (distance < key[i][j]) {
                        key[i][j] = distance;
                        parent_i[i][j] = ui;
                        parent_j[i][j] = uj;
                    }
                }
            }
        }

        int ans = 0, i = rows - 1, j = cols - 1;
        while (!(i == 0 && j == 0)) {
            ans = max(ans, key[i][j]);
            int new_i = parent_i[i][j];
            int new_j = parent_j[i][j];
            i = new_i;
            j = new_j;
        }
        return ans;
    }
};