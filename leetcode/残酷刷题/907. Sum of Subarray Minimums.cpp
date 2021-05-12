#include <bits/stdc++.h>
using namespace std;
/*
总共有 n + ... + 1 = n(n+1)/2 个子串，肯定不能暴力枚举
注意到，对于数 arr[i]，作为最小值的最大范围是 [left[i]+1, right[i]-1]，算一下所有可能的子串，次数为 a * b，其中 a = (i - left[i]), b = (right[i] - i)
其中:
    right[i] 表示右边第一个比 arr[i] 小的下标
    left[i] 表示左边第一个比 arr[i] 小的下标
    利用单调栈求解
可能出现有相同数的情况，这种情况为了保证只选一个数，需要将排序按照 <arr[i], i> 来进行，使得比较方式唯一确定
*/
const int P = 1e9 + 7;
class Solution {
   public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        vector<pair<int, int>> a;
        // 哨兵
        a.push_back({-1, 0});
        for (int i = 0; i < n; i++) {
            a.push_back({arr[i], i + 1});
        }
        // 哨兵
        a.push_back({-1, n + 1});

        vector<int> left(n + 1), right(n + 1);
        stack<int> s;
        s.push(0);
        for (int i = 1; i <= n; i++) {
            while (a[s.top()] > a[i]) s.pop();
            left[i] = s.top();
            s.push(i);
        }
        s = stack<int>();
        s.push(n + 1);
        for (int i = n; i >= 1; i--) {
            while (a[s.top()] > a[i]) s.pop();
            right[i] = s.top();
            s.push(i);
        }

        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += (long long)a[i].first * (i - left[i]) * (right[i] - i);
        }
        return ans % P;
    }
};
