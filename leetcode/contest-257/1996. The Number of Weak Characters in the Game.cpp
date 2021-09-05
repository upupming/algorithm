#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int numberOfWeakCharacters(vector<vector<int>>& properties) {
        sort(properties.begin(), properties.end());
        priority_queue<pair<int, int>> pq;
        int n = properties.size();
        int ans = 0;
        for (int i = n - 1; i >= 0;) {
            int a = properties[i][0];
            int j = i;
            for (; j >= 0; j--) {
                if (properties[j][0] != a) break;
                if (pq.empty())
                    continue;
                else if (pq.top().first > properties[j][1])
                    ans++;
            }
            for (int k = i; k > j; k--) {
                pq.push({properties[k][1], properties[k][0]});
            }
            i = j;
        }
        return ans;
    }
};
