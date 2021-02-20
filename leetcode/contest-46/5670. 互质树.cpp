#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 2 * N;

/*
无向树遍历的套路：dfs 传入一个 `father`，避免反向遍历

如果直接存祖先路径上所有的数的话，在树是线性的时候复杂度会退化为 O(N^2)

但是，这个题目有个很重要的性质，就是 num[i] < 50，这样在找每个节点的 ans 的时候，可以直接暴力枚举 1~50，看是否互质，如果互质，在最近的哪一层
然后我们用 dep[t] 表示数 t 所在的离当前层的最近的层，-1 表示 t 在祖先中没有存在过
然后我们用 pos[t] 表示满足上述条件的数 t 的节点编号
*/

int ver[M], Next[M], head[N], tot;
int pos[60], dep[60];
class Solution {
    int n, m;
    vector<int> ans, nums;
    void add(int x, int y) {
        ver[++tot] = y;
        Next[tot] = head[x], head[x] = tot;
    }

    void dfs(int x, int fa, int depth) {
        for (int t = 1; t <= 50; t++) {
            // 如果祖先存在数 t 和 x 互质的话
            if (dep[t] != -1 && __gcd(t, nums[x]) == 1) {
                // 记录 pos 最大，也就是最深的那个祖先
                if (ans[x] == -1 || dep[t] > dep[nums[ans[x]]]) {
                    ans[x] = pos[t];
                }
            }
        }

        int b1 = dep[nums[x]], b2 = pos[nums[x]];
        dep[nums[x]] = depth, pos[nums[x]] = x;
        for (int i = head[x]; i; i = Next[i]) {
            int y = ver[i];
            if (y != fa) dfs(y, x, depth + 1);
        }
        dep[nums[x]] = b1, pos[nums[x]] = b2;
    }

   public:
    vector<int> getCoprimes(vector<int>& _nums, vector<vector<int>>& e) {
        memset(head, 0, sizeof head), tot = 0;
        nums = _nums;
        n = nums.size(), m = e.size();
        ans = vector<int>(n, -1);
        for (auto& t : e) {
            add(t[0], t[1]), add(t[1], t[0]);
        }
        memset(dep, -1, sizeof dep);
        dfs(0, -1, 0);
        return ans;
    }
};
