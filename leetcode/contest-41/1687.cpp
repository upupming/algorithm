#include <bits/stdc++.h>
using namespace std;
/*
f(i) 表示运送完前 i 个箱子所需要的最小行程数，i 的有效下标从 1 开始。
*/
typedef long long LL;
class Solution {
   public:
    int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight) {
        int n = boxes.size();
        vector<LL> w(n + 1, 0), c(n + 2, 0);
        for (int i = 1; i <= n; i++)
            w[i] = w[i - 1] + boxes[i - 1][1];
        for (int i = 2; i <= n; i++)
            c[i] = c[i - 1] + (boxes[i - 1][0] != boxes[i - 2][0]);
        vector<int> f(n + 1, INT_MAX);
        f[0] = 0;
        deque<int> q;
        q.push_back(0);
        for (int i = 1; i <= n; i++) {
            while (!q.empty() &&
                   (i - q.front() > maxBoxes || w[i] - w[q.front()] > maxWeight))
                q.pop_front();

            f[i] = f[q.front()] + c[i] - c[q.front() + 1] + 2;

            while (!q.empty() && f[i] - c[i + 1] < f[q.back()] - c[q.back() + 1])
                q.pop_back();

            q.push_back(i);
        }
        return f[n];
    }
};