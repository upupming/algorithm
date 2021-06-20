#include <bits/stdc++.h>
using namespace std;
const int N = 2e4 + 10;
struct Q {
    int s, e, idx;
} q[N];
class Solution {
   public:
    int cnt[110] = {0};
    int get() {
        int last = -1, ans = INT_MAX;
        for (int i = 1; i <= 100; i++) {
            if (cnt[i]) {
                // cout << i << endl;
                if (last != -1) ans = min(ans, i - last);
                last = i;
            }
        }
        if (ans == INT_MAX) return -1;
        return ans;
    }
    vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), m = queries.size();
        vector<int> ans(m);
        // cout << n << " " << m << endl;
        for (int i = 0; i < m; i++) {
            q[i] = {queries[i][0], queries[i][1], i};
        }
        const auto& cmp = [](auto& a, auto& b) {
            int lena = a.e - a.s + 1, lenb = b.e - b.s + 1;
            if (lena != lenb) return lena < lenb;
            return a.s < b.s;
        };
        sort(q, q + m, cmp);
        for (int k = q[0].s; k <= q[0].e; k++) {
            cnt[nums[k]]++;
        }
        ans[q[0].idx] = get();
        for (int i = 1; i < m; i++) {
            // cout << i << " " << q[i].idx << endl;
            int s = max(q[i].s, q[i - 1].e + 1), e = q[i].e;
            if (q[i].s >= q[i - 1].s) {
                for (int k = q[i - 1].s; k <= min(q[i - 1].e, q[i].s - 1); k++) {
                    cnt[nums[k]]--;
                }
                for (int k = s; k <= e; k++) {
                    cnt[nums[k]]++;
                }
            } else {
                for (int k = q[i].s; k <= q[i - 1].s - 1; k++) {
                    cnt[nums[k]]++;
                }
                for (int k = q[i].e + 1; k <= q[i - 1].e; k++) {
                    cnt[nums[k]]--;
                }
                for (int k = q[i - 1].e + 1; k <= q[i].e; k++) {
                    cnt[nums[k]]++;
                }
            }
            ans[q[i].idx] = get();
        }
        return ans;
    }
};
