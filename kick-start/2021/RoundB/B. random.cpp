#include <ctime>
#include <iostream>
using namespace std;

long long random(long long n) {
    return (long long)rand() * rand() % n;
}

int main() {
    // 必须用随机种子，不然每次生成的数据都是一样的
    srand((unsigned)time(0));

    int n = 6;
    cout << 1 << endl;
    for (int i = 1; i <= n; i++) cout << random(100) + 1 << " ";
    cout << endl;
    return 0;
}
