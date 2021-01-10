#include <bits/stdc++.h>
using namespace std;
/*
划分成 k 个集合，最小化「最大的集合和」
数据范围很小，直接爆搜
*/
class Solution {
    // s[i] 表示第 i 个集合的和是 i
    vector<int> jobs, s;
    int sk;
    int ans = INT_MAX;

    // 当前枚举到第 i 个数，要放到第 j 个集合里面
    // maxJ 表示当前已有的集合
    void dfs(int i, int j, int maxJ) {
        s[j] += jobs[i];
        // 剪枝体检终止
        if (s[j] > ans) {
            s[j] -= jobs[i];
            return;
        }

        if (i + 1 < jobs.size())
            // 枚举第 i + 1 个数的所有放置集合情况
            // k = j+1 表示放入一个新的集合里面
            for (int k = 0; k <= min(maxJ + 1, sk - 1); k++) {
                dfs(i + 1, k, max(maxJ, k));
            }
        else {
            int nowAns = 0;
            for (int x : s) {
                nowAns = max(nowAns, x);
            }
            ans = min(ans, nowAns);
        }

        s[j] -= jobs[i];
    }

   public:
    int minimumTimeRequired(vector<int>& _jobs, int k) {
        jobs = _jobs, sk = k;
        s.resize(k);
        dfs(0, 0, 0);
        return ans;
    }
};