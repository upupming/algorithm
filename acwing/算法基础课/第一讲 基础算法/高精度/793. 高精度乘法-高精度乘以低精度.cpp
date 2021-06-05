#include <iostream>
#include <vector>
using namespace std;

string a;
int b;

void out(vector<int> &A) {
    for (int i = A.size() - 1; i >= 0; i--) {
        cout << A[i];
    }
}

vector<int> mul(vector<int> &A, int b) {
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size(); i++) {
        int val = A[i] * b + t;
        C.push_back(val % 10);
        t = val / 10;
    }
    while (t) {
        C.push_back(t % 10), t /= 10;
    }
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

int main() {
    cin >> a >> b;
    vector<int> A;
    for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    auto C = mul(A, b);
    out(C);
    return 0;
}
