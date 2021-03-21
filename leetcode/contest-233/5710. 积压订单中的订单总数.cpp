#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
const int P = 1e9 + 7;
class Solution {
   public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        priority_queue<PII> buy;
        priority_queue<PII, vector<PII>, greater<PII>> sell;
        for (auto& o : orders) {
            // buy
            if (o[2] == 0) {
                while (o[1] && sell.size() && sell.top().first <= o[0]) {
                    if (sell.top().second <= o[1]) {
                        o[1] -= sell.top().second;
                        sell.pop();
                    } else {
                        auto now = sell.top();
                        sell.pop();
                        now.second -= o[1];
                        sell.push(now);
                        o[1] = 0;
                    }
                }
                if (o[1]) {
                    buy.push({o[0], o[1]});
                }
            } else {
                // sell
                while (o[1] && buy.size() && buy.top().first >= o[0]) {
                    if (buy.top().second <= o[1]) {
                        o[1] -= buy.top().second;
                        buy.pop();
                    } else {
                        auto now = buy.top();
                        buy.pop();
                        now.second -= o[1];
                        buy.push(now);
                        o[1] = 0;
                    }
                }
                if (o[1]) {
                    sell.push({o[0], o[1]});
                }
            }
            // cout << buy.size() << " " << sell.size() << endl;
        }
        int ans = 0;
        while (sell.size()) {
            ans = (ans + sell.top().second) % P;
            sell.pop();
        }
        while (buy.size()) {
            ans = (ans + buy.top().second) % P;
            buy.pop();
        }
        return ans;
    }
};
