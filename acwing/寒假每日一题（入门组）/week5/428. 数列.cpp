#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int k, n;
vector<int> ans;
int main() {
    cin >> k >> n;
    int i = 0;
    while (ans.size() < n) {
        int x = pow(k, i++);
        int m = ans.size();
        ans.push_back(x);
        for (int j = 0; j < m; j++) {
            ans.push_back(ans[j] + x);
        }
    }
    cout << ans[n - 1] << endl;
    return 0;
}