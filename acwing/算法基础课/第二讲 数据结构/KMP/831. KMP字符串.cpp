#include <iostream>
using namespace std;
const int N = 1e5 + 10, M = 1e6 + 10;

int n, m;
int Next[N];
char s[M], p[N];
int main() {
    cin >> n >> p + 1 >> m >> s + 1;
    for (int i = 2, j = 0; i <= n; i++) {
        while (j > 0 && p[i] != p[j + 1]) j = Next[j];
        if (p[i] == p[j + 1]) j++;
        Next[i] = j;
    }
    for (int i = 1, j = 0; i <= m; i++) {
        while (j > 0 && (j == n || s[i] != p[j + 1])) j = Next[j];
        if (s[i] == p[j + 1]) j++;
        if (j == n) {
            printf("%d ", i - n);
        }
    }
    return 0;
}
