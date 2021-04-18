#include <bits/stdc++.h>
using namespace std;

/*
就是求全排列中的字典序第几个
比如 cba = 4 + 1 + 0
4 表示长为 3 的字符串，第一位为 a/b，后面任意的方案总数 - 1
1 表示长为 2 的字符串，第一位为 a，后面任意的方案总数（这里只能为 b）-1
0 表示长为 1 的字符串，第一位为 b，后面任意的方案总数（这里只能为 b）- 1
*/

const int P = 1e9 + 7, N = 3010;
typedef long long LL;
LL A[N], A_p[N];
int qpow(int a, int b, int p) {
    int ans = 1 % p;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return ans;
}
class Solution {
    // 比如 3 个 a，1 个 b，答案就是 4! / 3! / 1!
    LL calc(unordered_map<char, int>& cnt) {
        int n = 0;
        LL ans = 1;
        for (auto& [ch, c] : cnt) {
            if (c == 0) continue;
            n += c;
            ans = ans * A_p[c] % P;
            // cout << c << " " << A_p[c] << " " << ans << endl;
        }
        // cout << n << " " << A[n] << endl;
        return ans * A[n] % P;
    }
    bool flag = false;

    void init() {
        if (!flag) {
            A[0] = 1, A_p[0] = 1;
            for (int i = 1; i < N; i++) {
                A[i] = A[i - 1] * i % P;
            }
            for (int i = 1; i < N; i++) {
                A_p[i] = A_p[i - 1] * qpow(i, P - 2, P) % P;
            }
            flag = true;
        }
    }
    string s;

   public:
    int makeStringSorted(int startIndex, unordered_map<char, int>& cnt) {
        if (startIndex == s.length() - 1) return 0;

        char t = s[startIndex];
        LL ans = 0;
        for (auto& [ch, c] : cnt) {
            // 第 1 位可以选 ch
            if (ch < t && c) {
                cnt[ch]--;
                ans = (ans + calc(cnt)) % P;
                cnt[ch]++;
            }
        }
        // cout << ans << endl;
        cnt[s[startIndex]]--;
        return (ans + makeStringSorted(startIndex + 1, cnt)) % P;
    }
    int makeStringSorted(string _s) {
        s = _s;
        init();
        unordered_map<char, int> cnt;
        for (auto& ch : s) {
            cnt[ch]++;
        }

        return makeStringSorted(0, cnt);
    }
};
