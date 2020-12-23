/*
暴力枚举最小循环元的宽度，然后在行与行之间应用 KMP 算法求 next 数组和最小循环元，注意这里求 next 数组的时候比较的不再是单个字符，而是每一行的字符串，n - next[n] 就是竖直方向的最短循环元长度
*/
#include <cstring>
#include <iostream>
using namespace std;
const int R = 1e4 + 10, C = 100;

char str[R][C];
int r, c, Next[R];
// st[j] 表示前宽度 j 是否满足同时是每一行的循环元，初始状态 false 表示满足，后续用 true 表示不满足
bool st[C];
int main() {
    cin >> r >> c;
    for (int i = 1; i <= r; i++) {
        cin >> str[i];
        // 总时间复杂度：O(C^2)，枚举所有的循环元 O(C)，每次验证是否是循环元 O(C)
        // 枚举循环元宽度 j
        for (int j = 1; j <= c; j++) {
            bool is_match = true;
            // 枚举重复字符串的起点：k = j, 2j, ...
            for (int k = j; k < c; k += j) {
                // 必须满足 row[0~j-1] == row[k~k+j-1] 才是循环元
                for (int u = 0; u < j && k + u < c; u++) {
                    if (str[i][u] != str[i][k + u]) {
                        is_match = false;
                        break;
                    }
                }
                if (!is_match) break;
            }
            if (!is_match) st[j] = true;
        }
    }

    // 暴力求出最小循环元的宽度，如果两个循环元宽度不同，易知宽度小的最后面积一定小（KMP 求的循环元也更小）
    int width;
    for (int i = 1; i <= c; i++)
        if (!st[i]) {
            width = i;
            break;
        }

    // 这里置为最小循环元，后续在竖直方向上使用 KMP 算法需要比较每行的循环元
    for (int i = 1; i <= r; i++) str[i][width] = '\0';

    for (int j = 0, i = 2; i <= r; i++) {
        while (j > 0 && strcmp(str[j + 1], str[i])) j = Next[j];
        if (!strcmp(str[j + 1], str[i])) j++;
        Next[i] = j;
    }

    int height = r - Next[r];

    cout << width * height << endl;

    return 0;
}