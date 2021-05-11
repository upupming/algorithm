#include <ctime>
#include <iostream>
#include <set>
using namespace std;

long long random(long long n) {
    return (long long)rand() * rand() % n;
}
set<int> v;
int main() {
    // 必须用随机种子，不然每次生成的数据都是一样的
    srand((unsigned)time(0));

    int n = 10, q = 100;
    cout << 1 << endl;
    cout << n << " " << q << endl;
    for (int i = 1; i < n; i++) {
        int fa = random(i) + 1;
        int l;
        do {
            l = random(10000);
        } while (v.count(l));
        v.insert(l);
        cout << fa << " " << i + 1 << " " << l << " " << random(10000) << endl;
    }
    for (int i = 1; i <= q; i++) {
        cout << random(n) + 1 << " " << random(10000) << endl;
    }
    cout << endl;
    return 0;
}
