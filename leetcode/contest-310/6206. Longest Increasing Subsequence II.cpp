const int N = 1e5 + 10;
typedef long long LL;
class Solution {
    int h[N] = {0}, a[N] = {0}, n;
    int lowbit(int x) {
        return x & (-x);
    }
    void updata(int x, int k) {
        while (x < N) {
            h[x] = k;
            int low = lowbit(x);
            for (int i = 1; i < low; i <<= 1)
                h[x] = max(h[x], h[x - i]);
            x += lowbit(x);
        }
    }
    int query(int x, int y) {
        int ans = 0;
        while (y >= x) {
            ans = max(a[y], ans), y -= 1;
            for (; y - lowbit(y) >= x; y -= lowbit(y))
                ans = max(h[y], ans);
        }
        return ans;
    }

   public:
    int lengthOfLIS(vector<int>& nums, int k) {
        n = nums.size();
        // vector<int> dp(N, 0);

        for (int i = 1; i <= n; i++) {
            int x = nums[i - 1];
            // int len = 1;
            // for (int j = max(1, a-k); j < a; j++) {
            //     len = max(len, dp[j] + 1);
            // }
            int len = max(1, int(query(max(1, x - k), x - 1)) + 1);
            // dp[a] = max(dp[a], len);
            // int oldVal = ask(a, a);

            // cout << x << " " << max(1, x-k) << " " << query(max(1, x-k), x-1) << " "<< len << endl;
            a[x] = len;
            updata(x, len);
        }
        int ans = 1;
        for (int i = 1; i <= n; i++) {
            int a = nums[i - 1];
            ans = max(ans, int(query(a, a)));
        }
        return ans;
    }
};
