#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n, x;
vector<int> a;
int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> x, a.push_back(x);
    sort(a.begin(), a.end());
    int m = unique(a.begin(), a.end()) - a.begin();
    cout << m << endl;
    for (int i = 0; i < m; i++)
        cout << a[i] << " ";
    return 0;
}