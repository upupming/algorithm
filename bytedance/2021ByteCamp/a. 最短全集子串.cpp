#include <bits/stdc++.h>
using namespace std;
const int N = 1e5;

string s;
int sum[26][N], n;
int pos, len;
unordered_set<char> st;
bool valid(int i, int j) {
    int cnt = 0;
    for (int k = 0; k < 26; k++) {
        if (sum[k][j] - sum[k][i - 1] >= 1) {
            cnt++;
        }
    }
    return cnt == st.size();
}
int main() {
    cin >> s;
    n = s.length();
    s = ' ' + s;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            sum[j][i] = sum[j][i - 1];
            if (j == s[i] - 'a') {
                sum[j][i] += 1;
            }
        }
        st.insert(s[i]);
    }
    pos = 1, len = n;
    for (int i = 1; i <= n; i++) {
        int l = i, r = n;
        if (!valid(i, r)) continue;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (valid(i, mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        int newLen = l - i + 1, newPos = i;
        if (newLen < len) {
            pos = i;
            len = newLen;
        }
    }

    cout << pos - 1 << "," << len << endl;
    return 0;
}
/*
abbbaaccb
*/
