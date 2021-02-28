#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        // 总让 nums1 的和 > nums2 的和
        int s1 = 0, s2 = 0;
        for (auto& a : nums1) s1 += a;
        for (auto& b : nums2) s2 += b;
        if (s1 < s2) {
            swap(s1, s2);
            swap(nums1, nums2);
        }
        int n = nums1.size(), m = nums2.size();
        // 无解
        if (n > m * 6) return -1;

        // max heap
        priority_queue<int> q1;
        // min heap
        priority_queue<int, vector<int>, greater<int>> q2;
        for (auto a : nums1) q1.push(a);
        for (auto b : nums2) q2.push(b);

        int ans = 0;
        int diff = s1 - s2;
        while (diff > 0) {
            int x1 = q1.top();
            q1.pop();
            int x2 = q2.top();
            q2.pop();

            ans++;
            int a = x1 - 1, b = 6 - x2;
            if (a > b) {
                diff -= a;
                q1.push(1), q2.push(x2);
            } else {
                diff -= b;
                q1.push(x1), q2.push(6);
            }
        }
        return ans;
    }
};
