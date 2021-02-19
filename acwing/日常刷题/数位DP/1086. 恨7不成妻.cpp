/*
https://www.acwing.com/solution/content/26575/
f[i][j][a][b] 表示所有这样的数的平方和：
1. 一共有 i 位
2. 最高位为 j
3. 数本身模 7 为 a
4. 各位数字之和模 7 为 b
转移：
枚举次高位填 k：
j*10^{i-1} + c == a
因此 c == a - j*10^{i-1}
f[i-1][k][a - j*10^{i-1}][b-j]
如果是直接求数的个数，肯定是 f[i][j][a][b] 直接加上面这个式子就行，但是答案要求的是平方和

对于所有的数（X 表示可以任意取）：
AX...X = A*power[i-1] + X...X
他们的平方和为：
(A*power[i-1])^2 * cnt + sigma (X...X)^2 + sigma 2 * (A * power[i-1] * (X...X))
cnt 是所有可能的数的个数
这里面需要用到所有数的和，就是：
A*power[i-1] * cnt + (X...X)
*/
#include <iostream>
#include <vector>
using namespace std;
const int N = 20, P = 1e9 + 7;
typedef long long LL;

struct F {
    // 满足条件的数的「数量」、「和」、「平方和」
    int s0, s1, s2;
} f[N][10][7][7];
// 10 的 i 次方模 7
int pow7[N];
// 10 的 i 次方模 P
LL powP[N];
int mod(LL x, LL y) {
    return (x % y + y) % y;
}
void init() {
    pow7[0] = powP[0] = 1;
    for (int i = 1; i < N; i++) {
        pow7[i] = pow7[i - 1] * 10ll % 7;
        powP[i] = powP[i - 1] * 10ll % P;
    }
    // 初始化
    for (int j = 0; j <= 9; j++) {
        if (j == 7) continue;
        F &v = f[1][j][j % 7][j % 7];
        v.s0 = 1, v.s1 = j, v.s2 = j * j;
    }
    // 递推计算
    for (int i = 2; i < N; i++) {
        for (int j = 0; j <= 9; j++) {
            if (j == 7) continue;
            for (int a = 0; a < 7; a++) {
                for (int b = 0; b < 7; b++) {
                    // 枚举次高位填 k
                    for (int k = 0; k <= 9; k++) {
                        F &x = f[i][j][a][b], y = f[i - 1][k][mod(a - j * pow7[i - 1], 7)][mod(b - j, 7)];
                        // 直接加上 y 的数量
                        x.s0 = mod(x.s0 + y.s0, P);
                        // 除了加上 y 的和，还需要以 j 开头后面全 0 的数计算 cnt（y.s0） 次
                        x.s1 = mod(x.s1 + y.s1 + powP[i - 1] * j % P * y.s0, P);
                        x.s2 = mod(
                            x.s2 +
                                // (j * 10^{i-1})^2 * cnt
                                powP[i - 1] * powP[i - 1] % P * j * j % P * y.s0 +
                                // sigma 2 * (j * power[i-1] * (X...X))
                                // sigma (X...X) = y.s1
                                2 * j * powP[i - 1] % P * y.s1 +
                                // sigma (X...X)^2 = y.s2
                                y.s2,
                            P);
                    }
                }
            }
        }
    }
}

// 得到数 模7不为a，数位和模7不为b的 数的集合
F get(int i, int j, int a, int b) {
    int s0 = 0, s1 = 0, s2 = 0;
    for (int x = 0; x < 7; x++)
        for (int y = 0; y < 7; y++) {
            if (x == a || y == b) continue;
            F v = f[i][j][x][y];
            s0 = (s0 + v.s0) % P;
            s1 = (s1 + v.s1) % P;
            s2 = (s2 + v.s2) % P;
        }
    return {s0, s1, s2};
}

int dp(LL n) {
    // 0 % 7 == 0，不合法
    if (n == 0) return 0;
    vector<int> a;
    // 备份一下，最后会需要用到
    LL nn = n % P;
    while (n) a.push_back(n % 10), n /= 10;
    int len = a.size();

    int ans = 0;
    // 前面的数，前面的数位和
    LL last_a = 0, last_b = 0;
    for (int i = len - 1; i >= 0; i--) {
        int x = a[i];
        // 左侧分支：选择 1~(x-1) 来填
        for (int j = 0; j < x; j++) {
            if (j == 7) continue;
            // 1. 数模 7 不能为 a
            int a = mod(-last_a * pow7[i + 1], 7);
            // 2. 数位和模 7 不能为 b
            int b = mod(-last_b, 7);
            F v = get(i + 1, j, a, b);
            ans = mod(ans +
                          // last_a * 10^(i+1) * cnt（v.s0）
                          last_a % P * (last_a % P) % P * powP[i + 1] % P * powP[i + 1] % P * v.s0 +
                          //    sigma 2 * last_a * 10^{i+1} * (X...X)
                          //    sigma (X...X) = v.s1
                          2 * last_a % P * powP[i + 1] % P * v.s1 +
                          // sigma (X...X)^2 = v.s2
                          v.s2,
                      P);
        }
        // 右侧分支：选择 x 来填
        if (x == 7) break;
        last_a = last_a * 10 + x;
        last_b += x;
        if (i == 0 && last_a % 7 && last_b % 7)
            ans = mod(ans + nn * nn, P);
    }
    return ans;
}
LL l, r, t;
int main() {
    init();
    cin >> t;
    while (t--) {
        cin >> l >> r;
        cout << mod(dp(r) - dp(l - 1), P) << endl;
    }
    return 0;
}
