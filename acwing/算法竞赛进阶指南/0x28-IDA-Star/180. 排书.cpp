/*
在每个状态下，我们可以抽取连续的一段书，移动到另一个位置。
对于任意 i 当抽取长度为 i 时，有 n - i + 1 种选择方法，有 n - i 个可插入的位置。由于把一段书移动到更靠前的某个位置等价于把跳过的那段书移动到靠后的某个位置。因此，我们可以只枚举向后移动，而不枚举向前移动的情况。
按照书上的公式，不难算出每个状态的分支数量约为 560
根据题目要求，我们只需要考虑 4 次操作以内能否实现目标，我们只需要考虑搜索树的前 4 层，总复杂度 560^4 无法承受
1. 双向 BFS
2. IDA*
在目标状态下，第 i 本书后边应该是第 i + 1 本书，我们称 i + 1 是 i 的正确后继
当前状态错误后继总数为 tot，因为每次操作至多把 3 本书更改对，所以后续至少需要 tot/3 向上取整次操作，f(s) = tot/3 向上取整

剪枝：若当前深度+未来估计步数 > 深度限制，则立即从当前分支回溯
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 15;

int n, t, b[N], e, cpy[5][N];
// 计算
int totCnt() {
    int tot = 0;
    for (int i = 0; i < n - 1; i++) {
        // 这里之前写错了结果一直错
        if (b[i] + 1 != b[i + 1]) tot++;
    }
    return tot;
}
void out() {
    for (int i = 0; i < n; i++) cout << b[i] << " ";
    cout << endl;
}
// dep: 已经用了多少步
bool dfs(int dep) {
    int tot = totCnt();
    if (dep + (tot + 2) / 3 > e) return false;
    if (tot == 0) return true;

    // 序列长度
    for (int i = 1; i <= n - 1; i++) {
        // 第几个序列
        for (int j = 0; j < n - i + 1; j++) {
            // 所有可以插入的位置
            for (int k = j + 1; k < n - i + 1; k++) {
                // 为了防止 cpy 被其他分支篡改，必须每一个 dep 一个数组，因为一个 dep 每次只会迭代到一个分支，但是栈中可能存在多个 dep 不同的回溯路径
                memcpy(cpy[dep], b, sizeof(b));
                // 将 [j, j+i) 移动到 i+k 开头的地方
                // cout << i << " " << j << " " << k << endl;
                for (int l = j; l < k + i; l++) {
                    // cout << l << " " << l + i << " " << j + l - k << endl;
                    if (l < k)
                        b[l] = cpy[dep][l + i];
                    else {
                        b[l] = cpy[dep][j + l - k];
                    }
                }
                // out();
                if (dfs(dep + 1)) return true;

                memcpy(b, cpy[dep], sizeof(b));
            }
        }
    }
    return false;
}
int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> b[i];
        e = 0;
        bool ok = 0;
        while (e <= 4) {
            if (dfs(0)) {
                cout << e << endl;
                ok = 1;
                break;
            }
            e++;
        }
        if (!ok) cout << "5 or more" << endl;
    }
    return 0;
}
