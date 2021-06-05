/*
减法模拟除法: https://www.bilibili.com/video/BV1iK4y1L7om/?spm_id_from=333.788.videocard.8

例子:
78945/345
78945-34500*2 = 9945 (不断减 34500 直到不够减为止)
9945-3450*2 = 3045
3045-345*8= 285
因此，商就是 228, 余数就是 285

总时间复杂度: O(n-m * (n))，只能通过 8/12 个测试数据，因此能用「高精度/低精度」尽量不用「高精度/高精度」
*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

string a, b;

// A < B
bool cmp(const vector<int> &A, const vector<int> &B) {
    if (A.size() != B.size()) {
        return A.size() < B.size();
    }
    for (int i = A.size() - 1; i >= 0; i--) {
        if (A[i] != B[i]) return A[i] < B[i];
    }
    return false;
}
// A>=B
vector<int> sub(const vector<int> &A, const vector<int> &B) {
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

// O(n-m * (n)), 对于每个补 0 后的 B，最多执行 10 次时间复杂度为 O(n) 的高精度减法
// 注意 A 会被修改，所以这里不使用引用
// 不是很想写引用，因为别人调用的时候 div(A, B, A) 的话还得手动复制一遍 A 调用 div(A, B, A_copy)，不然对结果 A 进行修改会使输入 A 出问题
pair<vector<int>, vector<int>> div(vector<int> A, const vector<int> &B) {
    vector<int> C, R;
    int n = A.size(), m = B.size(), d = n - m;
    C.resize(d + 1, 0);
    // 枚举补 0 的个数
    for (int len = d; len >= 0; len--) {
        // Bp (B padded) 的构造可以外提优化，需要使用 deque 每次 pop_front，但是这里没有必要，因为时间复杂度主要瓶颈在下面循环的高精度减法上
        vector<int> Bp(len, 0);
        for (int x : B) Bp.push_back(x);

        // A >= Bp
        while (!cmp(A, Bp)) {
            C[len] += 1;
            A = sub(A, Bp);
        }
    }
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    R = A;
    return make_pair(C, R);
}

void out(vector<int> &A) {
    for (int i = A.size() - 1; i >= 0; i--) {
        cout << A[i];
    }
}

int main() {
    cin >> a >> b;
    vector<int> A, B;
    for (int i = a.length() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for (int i = b.length() - 1; i >= 0; i--) B.push_back(b[i] - '0');
    auto [C, R] = div(A, B);
    out(C);
    cout << endl;
    out(R);
    return 0;
}
