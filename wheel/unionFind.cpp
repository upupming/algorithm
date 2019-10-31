#include <iostream>

using namespace std;

int find(int parent[], int i) {
    if (parent[i] == -1) return i;
    else return find(parent, parent[i]);
}
void Union(int parent[], int x, int y) {
    int xRoot = find(parent, x);
    int yRoot = find(parent, y);
    if (xRoot != yRoot) parent[xRoot] = yRoot;
}

int a[3][3] = {
    0, 1, 1,
    1, 0, 1,
    1, 1, 0
};
int b[3][3] = {
    0, 1, 0,
    1, 0, 1,
    0, 1, 0
};

void print(int parent[], int n) {
    for (int i = 0; i < n; i++) {
        cout << parent[i] << " ";
    }
    cout << endl;
}

// 判断图是否有环
bool hasCircle(int a[][3]) {
    int *parent = new int[3]{-1, -1, -1};
    for (int i = 0; i < 3; i++) {
        // 防止重复计算
        for (int j = i + 1; j < 3; j++) {
            if (a[i][j] == 1) {
                int iRoot = find(parent, i), jRoot = find(parent, j);
                if (iRoot == jRoot) {
                    // cout << iRoot << ", " << jRoot << endl;
                    print(parent, 3);
                    return true;
                }
                else Union(parent, iRoot, jRoot);
                // print(parent, 3);
            }
        }
    }
    return false;
}

int main() {
    cout << hasCircle(a) << endl;
    cout << hasCircle(b) << endl;
    return 0;
}