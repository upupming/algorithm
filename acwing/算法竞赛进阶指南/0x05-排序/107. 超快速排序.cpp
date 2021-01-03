#include <iostream>
using namespace std;

// 逆序对，归并排序的应用

int n, a[500010], b[500010];
long long cnt;

// a[l-mid] 和 a[mid-r] 的逆序对数
void merge(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    merge(l, mid), merge(mid + 1, r);

    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (j > r || i <= mid && a[i] <= a[j])
            b[k] = a[i++];
        else
            b[k] = a[j++], cnt += mid - i + 1;
    }
    for (int k = l; k <= r; k++) a[k] = b[k];
}

void solve() {
    cnt = 0;
    merge(0, n - 1);
    cout << cnt << endl;
}

int main() {
    while (true) {
        cin >> n;
        if (n == 0) break;
        for (int i = 0; i < n; i++) cin >> a[i];
        solve();
    }

    return 0;
}
