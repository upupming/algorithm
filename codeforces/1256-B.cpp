#include <iostream>

using namespace std;

// 数组 shift、递归

int q, n, a[110];
bool useB;
void minS(int start, int end) {
    if (start >= end) return;
    // cout << start << ", " << end << endl;
    int index, minV = 0x3FFFFFFF;
    for (int i = start; i <= end; i++) {
        if (a[i] < minV) {
            minV = a[i];
            index = i;
        }
    }
    for (int i = index; i > start; i--) {
        a[i] = a[i - 1];
    }
    a[start] = minV;
    
    // for (int i = 0; i < n; i++) {
    //     if (i != 0) cout << " ";
    //     cout << a[i];
    // }
    // cout << endl;

    minS(index == start ? index + 1 : index, end);
}

int main() {
    cin >> q;
    while (q--) {
        useB = false;
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        minS(0, n - 1);
        for (int i = 0; i < n; i++) {
            if (i != 0) cout << " ";
            cout << a[i];
        }
        cout << endl;
    }
    return 0;
}

/*
100
5
5 4 1 3 2
4
1 2 4 3
1
1
4
4 3 2 1
1
1
2
1 2
2
2 1
3
1 2 3
3
1 3 2
3
2 3 1
3
2 1 3
3
3 1 2
3
3 2 1
4
4 2 3 1
5
5 4 3 2 1
8
5 4 3 1 2 8 7 6
10

4
5
1 4 5 2 3
5
2 5 1 4 3
*/