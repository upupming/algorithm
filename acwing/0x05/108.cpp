#include <iostream>
using namespace std;

// 逆序对，归并排序的应用

int n, a[250010], b[250010], c[250010], cnt1, cnt2;

// a[l-mid] 和 a[mid-r] 的逆序对数
void merge(int *a, int l, int r, int &cnt) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    merge(a, l, mid, cnt), merge(a, mid + 1, r, cnt);

    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (j > r || i <= mid && a[i] <= a[j])
            c[k] = a[i++];
        else
            c[k] = a[j++], cnt += mid - i + 1;
    }
    for (int k = l; k <= r; k++) a[k] = c[k];
}

void solve() {
    // 多测试 case 的时候一定记得初始化变量
    cnt1 = cnt2 = 0;
    // 注意这里是 -2，因为 0没有算入，总元素个数是 n * n - 1
    merge(a, 0, n * n - 2, cnt1);
    merge(b, 0, n * n - 2, cnt2);
    if ((cnt1 - cnt2) % 2 == 0)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}

int main() {
    while (cin >> n) {
        int cnt = 0, x;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                cin >> x;
                if (x) a[cnt++] = x;
            }
        cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                cin >> x;
                if (x) b[cnt++] = x;
            }
        solve();
    }

    return 0;
}
