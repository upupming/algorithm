#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    string maxValue(string n, int x) {
        int i = 0;
        if (n[0] == '-') {
            i = 1;
            while (i < n.length() && n[i] - '0' <= x) i++;
        } else {
            while (i < n.length() && n[i] - '0' >= x) i++;
        }
        // cout << i << endl;
        n.insert(i, to_string(x));
        return n;
    }
};
