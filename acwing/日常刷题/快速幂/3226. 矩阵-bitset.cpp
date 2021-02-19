/*
矩阵快速幂求 A^k，每次乘法时间复杂度为 m^3，需要运算 log k 次
总时间复杂度：O(n m^3 log k)

只能做到这个时间复杂度了，只能过前 5 个测试用例
墨染空大佬给的解法也只是手写 bitset，并加入了二分求 count 的优化
*/
#include <bitset>
#include <cstring>
#include <iostream>
using namespace std;
const int M = 1010;

int m, n, k;
bitset<M> a[M], b[M], b_T[M];
// c 存放答案
bitset<M> c[M];
string s;
// 存储 A^k
bitset<M> a_k[M], a_cp[M];
bitset<M> temp[M];

void out(bitset<M> a[M]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void mul(bitset<M> a[M], bitset<M> b[M], bitset<M> c[M]) {
    for (int i = 0; i < m; i++) {
        temp[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            b_T[j][i] = b[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            auto c = a[i] & b_T[j];
            // 偶数个 1 就是 0，所以是 & 1
            temp[i][j] = temp[i][j] ^ (c.count() & 1);
        }
    }

    for (int i = 0; i < m; i++) {
        c[i] = temp[i];
    }
}

void qmi(int k) {
    // a_cp 是快速幂里面的临时变量
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            // 初始化为 a 矩阵
            a_cp[i][j] = a[i][j];
            // 初始化为单位矩阵
            if (i == j)
                a_k[i][j] = 1;
            else
                a_k[i][j] = 0;
        }
    }

    // 快速幂模板
    while (k) {
        if (k & 1) {
            mul(a_k, a_cp, a_k);
        }
        mul(a_cp, a_cp, a_cp);
        k >>= 1;
    }
}

int main() {
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> s;
        for (int j = 0; j < m; j++) {
            a[i][j] = s[j] - '0';
        }
    }
    cin >> s;
    for (int i = 0; i < m; i++)
        b[i][0] = s[i] - '0';

    cin >> n;
    while (n--) {
        cin >> k;
        qmi(k);
        mul(a_k, b, c);
        for (int i = 0; i < m; i++)
            cout << c[i][0];
        cout << endl;
    }
    return 0;
}
