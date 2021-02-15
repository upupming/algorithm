#include <ctime>
#include <iostream>
using namespace std;

int random(int n) {
    return (long long)rand() * rand() % n;
}

int main() {
    // 必须用随机种子，不然每次生成的数据都是一样的
    srand((unsigned)time(0));

    int n = 5, q = 5;
    cout << 1 << endl;
    cout << n << " " << q << endl;
    for (int i = 1; i <= n; i++) cout << random(100) + 1 << " ";
    cout << endl;
    while (q--) {
        char op = random(2) ? 'U' : 'Q';
        cout << op << " ";
        if (op == 'Q') {
            int l = random(n) + 1, r = random(n) + 1;
            if (l > r) swap(l, r);
            cout << l << " " << r << endl;
        } else {
            int x = random(100) + 1;
            int i = random(n) + 1;
            cout << i << " " << x << endl;
        }
    }
    return 0;
}