#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

string a;
int b;

vector<int> div(const vector<int>& A, int b, int& r) {
    vector<int> C;
    r = 0;
    for (int i = A.size() - 1; i >= 0; i--) {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r = r % b;
    }
    reverse(C.begin(), C.end());
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

void out(vector<int>& A) {
    for (int i = A.size() - 1; i >= 0; i--) {
        cout << A[i];
    }
}

int main() {
    cin >> a >> b;
    vector<int> A;
    for (int i = a.length() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    vector<int> C;
    int r;
    C = div(A, b, r);
    out(C);
    cout << endl
         << r << endl;
    return 0;
}
