#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class Solution {
   public:
    int chalkReplacer(vector<int>& chalk, int k) {
        int n = chalk.size();
        LL sum = 0;
        for (auto c : chalk) sum += c;
        LL K = k;
        K %= sum;
        for (int i = 0; i < n; i++) {
            if (K < chalk[i]) return i;
            K -= chalk[i];
        }
        return -1;
    }
};
