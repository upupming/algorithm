#include <bits/stdc++.h>
using namespace std;
/*
LCS，要求时间复杂度 O(n log n)，不能用 dp，要转化为 LIS 算法求解
*/
class Solution {
   public:
    int minOperations(vector<int>& target, vector<int>& arr) {
        int ans = 0;
        unordered_map<int, int> pos;
        for (int i = 0; i < target.size(); i++)
            pos[target[i]] = i;
        vector<int> a;
        for (auto x : arr) {
            if (pos.count(x)) a.push_back(pos[x]);
        }

        int len = 0;
        vector<int> q(a.size() + 1);
        for (int i = 0; i < a.size(); i++) {
            int l = 0, r = len;
            while (l < r) {
                int mid = l + r + 1 >> 1;
                if (q[mid] < a[i])
                    l = mid;
                else
                    r = mid - 1;
            }
            len = max(len, r + 1);
            q[r + 1] = a[i];
        }
        cout << endl;

        return target.size() - len;
    }
};