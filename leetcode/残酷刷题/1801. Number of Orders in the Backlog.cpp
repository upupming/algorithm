#include <bits/stdc++.h>
using namespace std;
/*
Buy 用最大堆存储，每次找值尽量大的
Sell 用最小堆存储，每次找值尽量小的
时间复杂度 O(n log n)
比任务分配更简单的在于，不需要维护 job 队列
*/
// price, count
typedef pair<int, int> PII;
class Solution {
   public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        priority_queue<PII> buy;
        priority_queue<PII, vector<PII>, greater<>> sell;

        for (auto& order : orders) {
            // 当前是 buy，找较小的 sell 订单
            if (order[2] == 0) {
                while (sell.size() && sell.top().first <= order[0]) {
                    // 一种 sell 全部用完
                    if (sell.top().second <= order[1]) {
                        order[1] -= sell.top().second;
                        sell.pop();
                    } else {
                        // 一种 sell 用部分
                        auto [price, count] = sell.top();
                        sell.pop();
                        sell.push({price, count - order[1]});
                        order[1] = 0;
                        break;
                    }
                }
                if (order[1] > 0) {
                    // 剩余的 buy 入堆
                    buy.push({order[0], order[1]});
                }
            }
            // 当前是 sell，找较大的 buy 订单
            else {
                while (buy.size() && buy.top().first >= order[0]) {
                    if (buy.top().second <= order[1]) {
                        order[1] -= buy.top().second;
                        buy.pop();
                    } else {
                        auto [price, count] = buy.top();
                        buy.pop();
                        buy.push({price, count - order[1]});
                        order[1] = 0;
                        break;
                    }
                }
                if (order[1] > 0) {
                    sell.push({order[0], order[1]});
                }
            }
        }

        long long ans = 0;
        while (buy.size()) {
            ans += buy.top().second;
            buy.pop();
        }
        while (sell.size()) {
            ans += sell.top().second;
            sell.pop();
        }
        const int P = 1e9 + 7;
        return ans % P;
    }
};
