/*
N 个点，M 条无向边，S 种石头，R 个菜单，将石头 (a1, ..., ak) 搬到同一点之后，可以变成一个新的石头 b
携带一个石头过一条边耗能 1，每次最多携带 1 个石头，石头可以暂存在任一点
求石头变成类别 1 需要的最小能量

https://leetcode-cn.com/circle/article/M1wbLj/comments/561310/

总时间复杂度为O((SN+MS+RN)log(SN))。
*/
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
typedef long long ll;
const ll INF = 1e12;

template <typename T>
void read(T &x) {
    x = 0;
    char c = getchar();
    T sig = 1;
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            sig = -1;
    for (; isdigit(c); c = getchar())
        x = (x << 3) + (x << 1) + c - '0';
    x *= sig;
}

class Solution {
    int n, m, s, r;

    int hash(int si, int ni) const { return si * (n + 1) + ni; };

   public:
    void solve(int case_num) {
        printf("Case #%d: ", case_num);
        read(n), read(m), read(s), read(r);
        vector<vector<int>> adj(n + 1), needed_by_recipe(s + 1);
        vector<vector<ll>> stone_cost(s + 1, vector<ll>(n + 1, INF)),
            recipe_cost(r, vector<ll>(n + 1));
        vector<vector<int>> ingredients_got(r, vector<int>(n + 1));
        vector<int> ingredients_need(r), product(r);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        for (int i = 0; i < m; ++i) {
            int u, v;
            read(u), read(v);
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }

        for (int city = 1; city <= n; ++city) {
            int stone_num;
            read(stone_num);
            for (int j = 0; j < stone_num; ++j) {
                int stone;
                read(stone);
                // cost[i][j]表示在第j个城市制造（或直接获得）一块第i种石头的代价
                stone_cost[stone][city] = 0;
                pq.push({0, hash(stone, city)});
            }
        }

        for (int i = 0; i < r; ++i) {
            read(ingredients_need[i]);
            for (int j = 0; j < ingredients_need[i]; ++j) {
                int ingredient;
                read(ingredient);
                // needed_by[i]记录第i种石头在哪些配方里被用到了（如果在某个配方里被用了多次，就记录多次）
                needed_by_recipe[ingredient].emplace_back(i);
            }
            read(product[i]);
        }
        // Dijkstra算法的性质可以保证，我们的这一方案，一定是在j城市制作第r_i种配方的最优方案。
        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();
            ll c = top.first;
            int u = top.second;
            int stone = u / (n + 1), city = u % (n + 1);
            if (c != stone_cost[stone][city])
                continue;
            for (int recipe : needed_by_recipe[stone]) {
                ingredients_got[recipe][city]++;
                // recipe_cost[ri][j]记录在第j个城市收集第r_i种配方的原料的成本
                ll nc = recipe_cost[recipe][city] += c;
                // 我们根据某一配方，在第jj个城市制造出一种新石头s_k。这样可以转移到状态(s_k,j)。
                if (ingredients_got[recipe][city] == ingredients_need[recipe]) {
                    if (nc < stone_cost[product[recipe]][city]) {
                        stone_cost[product[recipe]][city] = nc;
                        pq.push({nc, hash(product[recipe], city)});
                    }
                }
            }
            // 我们带着这块石头去另一个城市c_k。这样可以转移到状态(i,c_k)。
            for (int nxt : adj[city]) {
                if (c + 1 < stone_cost[stone][nxt]) {
                    stone_cost[stone][nxt] = c + 1;
                    pq.push({c + 1, hash(stone, nxt)});
                }
            }
        }
        ll ans = *min_element(stone_cost[1].begin(), stone_cost[1].end());
        printf("%lld\n", ans == INF ? -1 : ans);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    read(t);
    for (int i = 1; i <= t; ++i) {
        Solution solution = Solution();
        solution.solve(i);
    }
}
