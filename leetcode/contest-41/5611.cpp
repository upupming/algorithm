#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        int n = aliceValues.size();
        map<pair<int, int>, int> sum;
        for (int i = 0; i < n; i++) {
            sum[pair<int, int>(-aliceValues[i] - bobValues[i], -aliceValues[i])]++;
        }
        int bob = 0, alice = 0;
        for (int i = 0, aTurn = 1; i < n; i++, aTurn = !aTurn) {
            auto j = sum.begin();
            if (!aTurn) {
                auto s = sum.lower_bound(pair<int, int>(sum.begin()->first.first + 1, INT_MIN));
                if (s != sum.end())
                    j = s, j--;

                bob += (-j->first.first + j->first.second);
            } else {
                alice += -(j->first.second);
            }

            sum[j->first]--;
            if (!sum[j->first]) sum.erase(j->first);
        }
        // cout << alice << " " << bob << endl;
        if (alice == bob)
            return 0;
        else if (alice > bob)
            return 1;
        else
            return -1;
    }
};