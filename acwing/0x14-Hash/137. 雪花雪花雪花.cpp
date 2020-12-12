/*
手动实现开散列哈希表
*/
#include <iostream>
using namespace std;

const int N = 100010, P = 99991;
// head, next 默认初始化为 0 表示为空
int n, snow[N][6], head[N], nxt[N];

// 哈希函数，定义为 (sum a_i + product a_i) % p，p 取最接近 N 的质数，操作一次的时间复杂度为 O(N^2 / P)
int H(int *a) {
    int sum = 0, prod = 1;
    for (int i = 0; i < 6; i++) {
        sum = (sum + a[i]) % P;
        prod = ((long long)prod * a[i]) % P;
    }
    return (sum + prod) % P;
}

bool equal(int *a, int *b) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            bool eq = true;
            for (int k = 0; k < 6; k++) {
                if (a[(i + k) % 6] != b[(j + k) % 6]) {
                    eq = false;
                    break;
                }
            }
            if (eq) return true;

            eq = true;
            for (int k = 0; k < 6; k++) {
                if (a[(i + k) % 6] != b[(j - k + 6) % 6]) {
                    eq = false;
                    break;
                }
            }
            if (eq) return true;
        }
    }
    return false;
}

// 将 a 加入哈希表，返回之前是否已经有和 a 相同的雪花
bool insert(int *a, int i) {
    int key = H(a);
    // 遍历表头 head[key] 指向的链表，寻找形状相同的雪花
    for (int i = head[key]; i; i = nxt[i]) {
        if (equal(a, snow[i]))
            return true;
    }
    // 未找到相等雪花，执行插入
    nxt[i] = head[key];
    head[key] = i;
    return false;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 6; j++) {
            cin >> snow[i][j];
        }

        if (insert(snow[i], i)) {
            cout << "Twin snowflakes found." << endl;
            return 0;
        }
    }

    cout << "No two snowflakes are alike." << endl;
    return 0;
}