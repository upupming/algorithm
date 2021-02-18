/*
分成两个部分：
1. <= 基准值，数量为 cnt
2. >= 基准值
cnt >= k，在左半边找第 k 小数
cnt < k，在右半边找找第 k - cnt 小数
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;

int quick_sort(int q[], int l, int r, int k) {
    if (l >= r) return q[l];
    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j) {
        do i++;
        while (q[i] < x);
        do j--;
        while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    int cnt = j - l + 1;
    if (cnt >= k)
        return quick_sort(q, l, j, k);
    else
        return quick_sort(q, j + 1, r, k - cnt);
}

int n, k, q[N];
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &q[i]);
    printf("%d\n", quick_sort(q, 0, n - 1, k));
}
