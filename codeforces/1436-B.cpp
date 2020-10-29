/**
1 1 1 1 9
1 1 1 1 9
1 1 1 1 9
9 9 9 9 5

1 1 1 4
1 1 1 4
1 1 1 4
4 4 4 1

1 4
4 1

1 1 9
1 1 9
9 9 1
 */

#include <cmath>
#include <iostream>

using namespace std;

int t, n, m;

bool isPrime(int a) {
    if (a == 1) return false;
    if (a == 2) return true;
    for (int i = 2; i <= sqrt(a); i++) {
        if (a % i == 0) return false;
    }
    return true;
}

int getNextNonPrime(int curPrime) {
    int tmp = curPrime + 1;
    while (true) {
        if (!isPrime(tmp)) return tmp;
        tmp++;
    }
}

void print(int val1, int val2) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            cout << 1 << " ";
        }
        cout << val1 << endl;
    }
    for (int j = 0; j < n - 1; j++) {
        cout << val1 << " ";
    }
    cout << val2 << endl;
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        int val1 = 1;
        // first line/column
        while (!isPrime((n - 1) + val1)) {
            val1 = getNextNonPrime(val1);
        }
        int tmp2 = val1 * (n - 1), val2 = 1;
        while (!isPrime(tmp2 + val2)) {
            val2 = getNextNonPrime(val2);
        }

        print(val1, val2);
    }
    return 0;
}