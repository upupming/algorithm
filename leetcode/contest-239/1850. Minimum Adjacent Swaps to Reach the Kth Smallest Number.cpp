#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int getMinSwaps(string num, int k) {
        string target(num);
        for (int i = 0; i < k; ++i)
            next_permutation(target.begin(), target.end());

        int ans = 0, n = num.size();
        for (int i = 0; i < n; ++i) {
            if (num[i] != target[i]) {
                int j = i + 1;
                while (num[j] != target[i])
                    j++;
                for (; j > i; --j)
                    swap(num[j], num[j - 1]), ans++;
            }
        }

        return ans;
    }
};
