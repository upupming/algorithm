/*
1. 确定分界点 x（左端点、中间点或者右端点）
2. 根据 x 调整，划分成两个区间，<=x 的在左半边，>=x 的在右半边
3. 递归排序左右两半边

i 前边所有的数 <= x
j 右边所有的数 >= x
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 10;

int n;
int q[N];

void quick_sort(int q[], int l, int r) {
    if (l >= r) return;
    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j) {
        do i++;
        while (q[i] < x);
        do j--;
        while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &q[i]);

    quick_sort(q, 0, n - 1);
    for (int i = 0; i < n; i++) printf("%d ", q[i]);
    return 0;
}
