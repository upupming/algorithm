#include <bits/stdc++.h>
using namespace std;

/*
告诉链表的所有边，输出原链表

遍历无向树
dfs参数u, father，遍历不是 father 的时候往下遍历

两个端点被给出的次数为 1，中间元素间给出的次数为 2
// 可以用 map，用数组的话 -10^5 要加个偏移量
*/

class Solution {
    map<int, int> cnt;
    // 邻接表
    unordered_map<int, vector<int>> g;
    vector<int> ans;

   public:
    void dfs(int x, int father) {
        ans.push_back(x);
        for (auto& y : g[x]) {
            if (y != father) {
                dfs(y, x);
            }
        }
    }
    vector<int> restoreArray(vector<vector<int>>& a) {
        for (int i = 0; i < a.size(); i++) {
            int x = a[i][0], y = a[i][1];
            g[x].push_back(y), g[y].push_back(x);
            cnt[x]++, cnt[y]++;
        }
        int side;
        for (auto p : cnt) {
            if (p.second == 1) {
                side = p.first;
                break;
            }
        }
        dfs(side, side);
        return ans;
    }
};