#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();
        vector<int> idx(n);
        for (int i = 0; i < n; i++) idx[i] = i;
        sort(idx.begin(), idx.end(), [&capital](int i, int j) {
            return capital[i] < capital[j];
        });
        int i = 0;
        priority_queue<int> pq;
        while (i < n && capital[idx[i]] <= w) {
            pq.push(profits[idx[i]]);
            i++;
        }
        while (pq.size() && k--) {
            w += pq.top();
            pq.pop();
            while (i < n && capital[idx[i]] <= w) {
                pq.push(profits[idx[i]]);
                i++;
            }
        }
        return w;
    }
};
