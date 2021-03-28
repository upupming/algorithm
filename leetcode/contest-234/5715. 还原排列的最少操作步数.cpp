#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool notOk(vector<int> &perm) {
        for (int i = 0; i < perm.size(); i++) {
            if (perm[i] != i) return true;
        }
        return false;
    }
    int reinitializePermutation(int n) {
        vector<int> perm(n), arr(n);
        for (int i = 0; i < n; i++) perm[i] = i;

        int cnt = 0;
        do {
            for (int i = 0; i < n; i++) {
                if (i % 2 == 0)
                    arr[i] = perm[i / 2];
                else
                    arr[i] = perm[n / 2 + (i - 1) / 2];
            }
            for (int i = 0; i < n; i++) {
                perm[i] = arr[i];
            }
            cnt++;
            for (int i = 0; i < n; i++) {
                cout << perm[i] << " ";
            }
            cout << endl;
        } while (notOk(perm));
        return cnt;
    }
};
