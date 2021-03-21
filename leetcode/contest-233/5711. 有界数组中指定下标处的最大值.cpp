#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class Solution {
    int n, idx, mS;
    LL calc(int mid, int idx) {
        LL sum = 0;
        if (mid - idx >= 1) {
            int left = mid - idx;
            sum += (left + mid - 1ll) * idx / 2;
        } else {
            sum += (1ll + mid - 1) * (mid - 1) / 2;
            sum += (idx + 1ll - mid) * 1;
        }
        return sum;
    }
    bool valid(int mid) {
        LL sum = calc(mid, idx) + calc(mid, n - 1 - idx) + mid;
        // cout << mid << " " << calc(mid) << " " << calc(n - 1 - idx) << " " << mid << " " << sum << endl;
        if (sum <= mS) return true;
        return false;
    }

   public:
    int maxValue(int _n, int index, int maxSum) {
        n = _n, idx = index, mS = maxSum;
        int l = 1, r = 1e9;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (valid(mid))
                l = mid;
            else
                r = mid - 1;
        }
        return l;
    }
};
