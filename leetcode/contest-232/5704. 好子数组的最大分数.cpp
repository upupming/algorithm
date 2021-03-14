class Solution {
   public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = nums[k];
        vector<int> s(n), t(n);
        s[0] = t[n - 1] = -1;
        stack<int> stk;
        stk.push(nums[0]);
        for (int i = 1; i < n; i++) {
            if (stk.size() && stk.top() == nums[i]) {
                stk.pop();
            }
            if (!stk.size())
                s[i] = -1;
            else
                s[i] = stk.top();
            stk.push(nums[i]);
        }
        stack<int> stk2;
        stk.push(nums[n - 1]);
        for (int i = n - 2; i >= 0; i--) {
            if (stk2.size() && stk2.top() == nums[i]) {
                stk2.pop();
            }
            if (!stk2.size())
                t[i] = -1;
            else
                t[i] = stk2.top();
            stk2.push(nums[i]);
        }

        for (int i = k, j = k, m = nums[k]; i >= 0 && j < n;) {
            ans = max(ans, m * (j - i + 1));
            if (i == 0 && j == n - 1) {
                break;
            }
            if (i == 0) {
                m = min(m, nums[++j]);
            } else if (j == n - 1) {
                m = min(m, nums[--i]);
            } else {
                if (nums[i - 1] == nums[j + 1]) {
                    if (s[i - 1] > t[j + 1]) {
                        m = min(m, nums[--i]);
                    } else {
                        m = min(m, nums[++j]);
                    }
                } else if (nums[i - 1] > nums[j + 1]) {
                    m = min(m, nums[--i]);
                } else {
                    m = min(m, nums[++j]);
                }
            }
        }

        return ans;
    }
};
