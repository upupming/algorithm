#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    const int MOD = 1e9 + 7;
    bool isPow(int x) {
        return pow(2, (int)log2(x)) == x;
    }
    int countPairs(vector<int>& deliciousness) {
        sort(deliciousness.begin(), deliciousness.end());
        long long ans = 0;
        unordered_map<int, int> cnt;
        for (int i = 0, j = 1; i < deliciousness.size(); i++) {
            while (deliciousness[i] >= j) j *= 2;
            ans = (ans + cnt[j - deliciousness[i]]) % MOD;
            if (deliciousness[i] > 0 && isPow(deliciousness[i])) ans += cnt[0];
            cnt[deliciousness[i]]++;
        }
        return ans;
    }
};