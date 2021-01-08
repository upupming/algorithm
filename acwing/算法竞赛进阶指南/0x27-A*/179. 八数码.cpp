/*
BFS 搜索，每个状态对应一个排列，每次扩展就是把一个数字与空格交换
A*优化：每次移动智能把一个数字与空格交换，这样至多把一个数字向它在目标状态中的位置移近一步。任何一个状态 x 下，到目标状态的移动步数 g(x) >= 所有数字当前位置与目标位置的曼哈顿距离之和，将此值设置为 f(x) 即可

每个状态只需要在第一次被取出时扩展一次。需要使用 Hash 来记录每个八数码是否已经被取出并扩展过一次。
可以自己实现一个 hash 函数，使用 stl 的 unordered_set 即可
*/
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;
typedef pair<int, int> PII;

struct P {
    int a[3][3], dist;
    PII pos[10];
    string ans;
    // 最小堆
    bool operator<(const P& p) const {
        return dist > p.dist;
    }
    bool operator==(const P& other) const {
        for (int i = 0; i < 9; i++) {
            if (pos[i] != other.pos[i]) return false;
        }
        return true;
    }
};
void out(P& p) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << p.a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
namespace std {
template <>
struct hash<P> {
    std::size_t operator()(const P& p) const {
        string str = "";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                str += to_string(p.a[i][j]);
            }
        }

        return hash<string>()(str);
    }
};
}  // namespace std
unordered_map<P, int> v, manhattonCache;

string s;
// 计算状态和目标状态的所有元素的曼哈顿距离之和
int manhatton(P& p) {
    if (manhattonCache.count(p)) return manhattonCache[p];

    int ans = 0;
    for (int i = 1; i <= 9; i++) {
        int x = abs(p.pos[i].first - (i - 1) / 3) +
                abs(p.pos[i].second - (i - 1) % 3);
        ans += x;
    }

    manhattonCache[p] = ans;

    return ans;
}
int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
string dir = "durl";
bool valid(int x, int y) {
    return x >= 0 && x < 3 && y >= 0 && y < 3;
}

void mergeSort(int* a, int l, int r, int& cnt) {
    if (l >= r) return;
    int mid = l + r >> 1;
    mergeSort(a, l, mid, cnt), mergeSort(a, mid + 1, r, cnt);
    int i = l, j = mid + 1, k = 0;
    int b[8];
    while (i <= mid && j <= r) {
        if (a[i] <= a[j])
            b[k++] = a[i++];
        else
            b[k++] = a[j++], cnt += mid - i + 1;
    }
    while (i <= mid)
        b[k++] = a[i++];
    while (j <= r)
        b[k++] = a[j++], cnt += mid - i + 1;
    for (int i = l; i <= r; i++) a[i] = b[i - l];
}
bool isSolvable(const P& p) {
    // 盲猜一下目标的逆序对数的奇偶性为：偶数（不对再改）
    int a[8], k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (p.a[i][j] == 9) continue;
            a[k++] = p.a[i][j];
        }
    }
    int cnt = 0;
    mergeSort(a, 0, 7, cnt);
    if (cnt % 2 == 0) return true;
    return false;
}

int main() {
    P start;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> s;
            if (s[0] == 'x') {
                // 用 9 来表示空格，这样目标状态是有序的，方便处理一些
                start.a[i][j] = 9;
                start.pos[9] = {i, j};
            } else {
                int num = s[0] - '0';
                start.a[i][j] = num;
                start.pos[num] = {i, j};
            }
        }
    }
    start.dist = 0 + manhatton(start);
    start.ans = "";

    if (!isSolvable(start)) {
        cout << "unsolvable" << endl;
        return 0;
    }

    // 因为是用的 A* 算法（权值加上了 f 函数的），所以还是要用优先队列
    priority_queue<P> q;
    q.push(start);
    int i = 0;
    while (q.size()) {
        auto now = q.top();
        q.pop();

        if (v.count(now)) continue;
        if (manhatton(now) == 0) {
            cout << now.ans << endl;
            return 0;
        }
        v[now]++;

        int d = now.dist - manhatton(now);
        // 拓展
        auto backspace = now.pos[9];
        for (int i = 0; i < 4; i++) {
            int x = backspace.first + dx[i];
            int y = backspace.second + dy[i];
            if (!valid(x, y)) continue;
            // 计算新的状态 next
            auto next = now;
            // 跟空格交换的数
            int num = now.a[x][y];
            swap(next.pos[9], next.pos[num]);
            swap(next.a[x][y], next.a[backspace.first][backspace.second]);
            if (v.count(next)) continue;

            next.dist = d + manhatton(next) + 1;
            next.ans += dir[i];
            q.push(next);
        }
    }
    return 0;
}