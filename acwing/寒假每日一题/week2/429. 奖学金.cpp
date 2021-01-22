#include <algorithm>
#include <iostream>
using namespace std;
const int N = 310;

struct Grade {
    int c, m, e, sum, idx;
    bool operator<(Grade& g) const {
        if (sum == g.sum) {
            if (c == g.c) {
                return idx < g.idx;
            }
            return c > g.c;
        }
        return sum > g.sum;
    }
} grade[N];
int n;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> grade[i].c >> grade[i].m >> grade[i].e;
        grade[i].sum = grade[i].c + grade[i].m + grade[i].e;
        grade[i].idx = i;
    }
    sort(grade + 1, grade + n + 1);
    for (int i = 1; i <= 5; i++) {
        cout << grade[i].idx << " " << grade[i].sum << endl;
    }
    return 0;
}