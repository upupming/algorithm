#include <iostream>
#include <vector>
using namespace std;

string a, b;

// A>=B
vector<int> sub(vector<int> &A, vector<int> &B) {
    vector<int> C;
    for (int i = 0, t = 0; i < A.size(); i++) {
        // 如果借过位，需要减去 t（t 是借位数量）
        t = A[i] - t;
        if (i < B.size()) t -= B[i];
        C.push_back((t + 10) % 10);
        // < 0  表示从高位借了一位出来了，所以 t = 1
        if (t < 0)
            t = 1;
        else
            t = 0;
    }
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

void out(vector<int> &A) {
    for (int i = A.size() - 1; i >= 0; i--) {
        cout << A[i];
    }
}

// A < B
bool cmp(vector<int> &A, vector<int> &B) {
    if (A.size() != B.size()) {
        return A.size() < B.size();
    }
    for (int i = A.size() - 1; i >= 0; i--) {
        if (A[i] != B[i]) return A[i] < B[i];
    }
    return false;
}

int main() {
    cin >> a >> b;
    vector<int> A, B;
    bool flag = false;
    for (int i = a.size() - 1; i >= 0; i--) {
        A.push_back(a[i] - '0');
    }
    for (int i = b.size() - 1; i >= 0; i--) {
        B.push_back(b[i] - '0');
    }
    // A < B 时需要调换位置
    if (cmp(A, B)) {
        flag = true;
        swap(A, B);
    }
    auto C = sub(A, B);
    if (flag) cout << "-";
    out(C);
    return 0;
}
