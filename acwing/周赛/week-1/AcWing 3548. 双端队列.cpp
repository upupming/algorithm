#include <deque>
#include <iostream>
using namespace std;
const int N = 2e5 + 10;

/*
想复杂了，直接允许负数下标，维护当前的左右下标 L 和 R 就可以了
*/

int q, x, lft[N], rht[N], idx[N];
string op;
deque<int> dq;
bool isLeft[N];
int main() {
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> op >> x;
        if (op != "?") idx[x] = i;
        if (op == "L") {
            dq.push_front(x), lft[i] = lft[i - 1] + 1, isLeft[x] = true;
            rht[i] = rht[i - 1];
        } else if (op == "R") {
            dq.push_back(x), rht[i] = rht[i - 1] + 1, isLeft[x] = false;
            lft[i] = lft[i - 1];
        } else {
            lft[i] = lft[i - 1], rht[i] = rht[i - 1];
            int j = idx[x];
            // cout << i << " " << j << " " << isLeft[x] << endl;
            int cntL, cntR;
            if (isLeft[x]) {
                cntL = lft[i] - lft[j];
                cntR = dq.size() - cntL - 1;
            } else {
                cntR = rht[i] - rht[j];
                cntL = dq.size() - cntR - 1;

                // cout << rht[i] << " " << rht[j] << " " << cntL << " " << cntR << endl;
            }
            cout << min(cntL, cntR) << endl;
        }
    }
    return 0;
}
