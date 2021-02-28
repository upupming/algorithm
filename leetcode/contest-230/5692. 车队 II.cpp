#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
typedef pair<double, double> PDD;
#define x first
#define y second

/*
暴力做法：每个车，看这个车追上前面所有可能的车的时间，求一个 min 即可
优化：每个点，求和后面所有点的斜率的最小值
*/

// https://www.nagwa.com/en/explainers/175169159270/
double cross(double x1, double y1, double x2, double y2) {
    return x1 * y2 - x2 * y1;
}
// ab x ac，ac 在 ab 左侧时为正
double area(PDD a, PDD b, PDD c) {
    return cross(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

class Solution {
   public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        int n = cars.size();
        vector<double> ans(n, -1);
        vector<PDD> stk(n + 1);
        int top = 0;
        for (int i = n - 1; i >= 0; i--) {
            auto& c = cars[i];
            PDD p(c[0], c[1]);
            while (top >= 2 && area(p, stk[top], stk[top - 1]) <= 0) top--;
            if (top == 0)
                ans[i] = -1;
            else {
                auto& q = stk[top];
                if (p.y <= q.y)
                    ans[i] = -1;
                else
                    ans[i] = (q.x - p.x) / (p.y - q.y);
            }
            stk[++top] = p;
        }
        return ans;
    }
};
