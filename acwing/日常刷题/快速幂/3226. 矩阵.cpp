/*
矩阵快速幂求 A^k，每次乘法时间复杂度为 m^3，需要运算 log k 次
总时间复杂度：O(n m^3 log k)，只能过 5 个测试用例

矩阵快速幂参考：https://www.acwing.com/file_system/file/content/whole/index/content/3067/
*/
#include <cstring>
#include <iostream>
using namespace std;
const int M = 1010;

int m, n, k;
int a[M][M], b[M][M];
// c 存放答案
int c[M][M];
string s;
// 存储 A^k
int a_k[M][M], a_cp[M][M];
int temp[M][M];

void out(int a[][M]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void out(int b[M]) {
    for (int i = 0; i < m; i++) {
        cout << b[i] << endl;
    }
    cout << endl;
}
void mul(const int a[][M], const int b[][M], int c[][M]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            temp[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                temp[i][j] ^= a[i][k] & b[k][j];
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            c[i][j] = temp[i][j];
        }
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
