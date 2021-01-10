#include <bits/stdc++.h>
using namespace std;
class Solution {
    vector<int> f, sz;
    int find(int x) {
        return x == f[x] ? x : f[x] = find(f[x]);
    }

    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy)
            return;
        if (sz[fx] < sz[fy]) {
            f[fx] = fy;
            sz[fy] += sz[fx];
        } else {
            f[fy] = fx;
            sz[fx] += sz[fy];
        }
    }

   public:
    int minimumHammingDistance(vector<int>& s, vector<int>& t, vector<vector<int>>& a) {
        int n = s.size();
        f.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            f[i] = i;
            sz[i] = 1;
        }
        unordered_map<int, vector<int>> groups;
        for (int i = 0; i < a.size(); i++) {
            merge(a[i][0], a[i][1]);
        }
        for (int i = 0; i < n; i++) {
            // 一个连通块放在一起
            groups[find(i)].push_back(i);
        }

        int ans = 0;
        for (auto& g : groups) {
            auto idices = g.second;
            unordered_map<int, int> cnt;
            for (auto& idx : idices) {
                cnt[s[idx]]++;
            }
            for (auto& idx : idices) {
                if (cnt[t[idx]]) {
                    cnt[t[idx]]--;
                } else
                    ans++;
            }
        }

        return ans;
    }
};