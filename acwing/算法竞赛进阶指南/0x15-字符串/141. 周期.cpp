/*
KMP 算法的应用
当 i - next[i] 能整除 i 时，s[1~i-next[i]] 就是 s[1~i] 的最小循环元
*/
#include <iostream>
using namespace std;
const int N = 1000010;

int n, t, Next[N];
char s[N];
void calcNext() {
    // KMP 模板
    Next[1] = 0;
    // j 的值在 while 循环中不断减小，j = Next[j] 的执行次数不会超过每层 for 循环开始时 j 的值与 while 循环结束时 j 的值之差
    // 每层 for 循环，j 的值至多增加 1，j 始终非负，因此减小幅度总和不会超过增加幅度总和
    // j 的变化次数至多为 2(N +M)，算法时间复杂度为 O(N + M)
    for (int i = 2, j = 0; i <= n; i++) {
        while (j > 0 && s[i] != s[j + 1]) j = Next[j];
        if (s[i] == s[j + 1]) j++;
        Next[i] = j;
    }
}
int main() {
    while (cin >> n, n) {
        // KMP 算法为了便于理解，避免处理负数问题，下标都从 1 开始
        scanf("%s", s + 1);
        calcNext();
        printf("Test case #%d\n", ++t);
        for (int i = 2; i <= n; i++) {
            if (i % (i - Next[i]) == 0 && i / (i - Next[i]) > 1) {
                printf("%d %d\n", i, i / (i - Next[i]));
            }
        }
        puts("");
    }
    return 0;
}