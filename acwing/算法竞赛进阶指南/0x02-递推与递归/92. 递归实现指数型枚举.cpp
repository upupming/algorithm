#include <iostream>
#include <vector>

using namespace std;

int n, p[60000];

// 手写的一个快速幂
int pow2(int x) {
    // 把 x 看做一个二进制数
    int ans = 1, a = 2;
    while (x > 0) {
        if (x & 1) ans *= a;
        a *= a;
        x >>= 1;
    }
    return ans;
}

// 位运算枚举方法
void solve() {
    for (int i = 0; i < pow2(n); i++) {
        int t = i, cnt = 0;
        for (int j = 1; t > 0; j++) {
            if (t & 1) {
                if (cnt)
                    cout << " ";
                cout << j, cnt++;
            }
            t >>= 1;
        }
        cout << endl;
    }
}

vector<int> arr;

void print() {
    for (int i = 0; i < arr.size(); i++) {
        if (i > 0)
            cout << " ";
        cout << arr[i];
    }
    cout << endl;
}

void dfs(int depth) {
    if (depth == n + 1) {
        print();
        return;
    }
    // case 1: 输出 depth
    arr.push_back(depth);
    dfs(depth + 1);
    // arr.erase(arr.end() - 1);
    arr.pop_back();
    // case 2: 不输出 depth
    dfs(depth + 1);
}

// 递归方法
void solve1() {
    dfs(1);
}

int main() {
    cin >> n;
    solve1();

    return 0;
}