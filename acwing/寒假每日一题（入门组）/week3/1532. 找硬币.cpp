/*
双指针：
先排序
i = 0, j = n-1
要求结果满足 a[i] + a[j] <= M
当 a[i] + a[j] > M 时，j --
当 a[i] + a[i] < M 是，i++
*/
#include <algorithm>
#include <iostream>
#include <unordered_set>
using namespace std;
const int N = 1e5 + 10;

int n, a[N], sum;

void solve_double_pointer() {
    sort(a, a + n);
    for (int i = 0, j = n - 1; i < j;) {
        if (a[i] + a[j] == sum) {
            cout << a[i] << " " << a[j] << endl;
            return;
        }
        if (a[i] + a[j] > sum)
            j--;
        else
            i++;
    }
    cout << "No Solution" << endl;
}

void solve_set() {
    unordered_set<int> s;
    for (int i = 0; i < n; i++) s.insert(a[i]);
    // O(M) 枚举每种组合情况
    for (int a = 1; a <= sum / 2; a++) {
        int b = sum - a;
        if (a == b) break;
        if (s.count(a) && s.count(b)) {
            cout << a << " " << b << endl;
            return;
        }
    }
    cout << "No Solution" << endl;
}

int main() {
    cin >> n >> sum;
    for (int i = 0; i < n; i++) cin >> a[i];
    // solve_double_pointer();
    solve_set();

    return 0;
}