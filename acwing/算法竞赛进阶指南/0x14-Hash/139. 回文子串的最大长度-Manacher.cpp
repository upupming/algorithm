/*
https://www.acwing.com/blog/content/2192/
除了暴力（[区间DP](https://leetcode-cn.com/problems/longest-palindromic-substring/solution/zui-chang-hui-wen-zi-chuan-by-leetcode-solution/)）、二分+哈希、后缀树组，Manacher 算法专门用来处理最长回文子串问题，时间复杂度为 O(N)

https://www.acwing.com/blog/content/2192/

https://www.acwing.com/blog/content/5031/
*/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 2000010;

int n, m, Case;
char s[N], str[N];
int p[N];

int manacher() {
    n = strlen(s);
    str[0] = '!', str[1] = '#'; /* str[0]为哨兵 */
    for (int i = 0; i < n; i++) {
        str[i * 2 + 2] = s[i];
        str[i * 2 + 3] = '#';
    }
    m = n * 2 + 1;
    str[m + 1] = '@'; /* 哨兵 */

    int rt = 0, mid = 0;
    int res = 0;
    for (int i = 1; i <= m; i++) {
        p[i] = i < rt ? min(p[2 * mid - i], rt - i) : 1;
        while (str[i + p[i]] == str[i - p[i]]) p[i]++;
        if (i + p[i] > rt) {
            rt = i + p[i];
            mid = i;
        }
        res = max(res, p[i] - 1);
    }
    return res;
}

int main() {
    while (scanf("%s", s), s[0] != 'E') {
        printf("Case %d: %d\n", ++Case, manacher());
    }
    return 0;
}
