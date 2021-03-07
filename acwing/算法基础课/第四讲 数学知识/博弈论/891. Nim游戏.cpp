#include <iostream>
using namespace std;

int n, a, s;
int main() {
    cin >> n;
    while (n--) {
        cin >> a;
        s ^= a;
    }
    if (s == 0) {
        puts("No");
    } else {
        puts("Yes");
    }
    return 0;
}
