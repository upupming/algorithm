#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t, a, b;
    string s;
    cin >> t;
    vector<int> in, out;
    while (t--) {
        out.clear();
        cin >> a >> b >> s;
        for (int i = 0; i < s.length(); i++) {
            int x;
            if (s[i] >= '0' && s[i] <= '9')
                x = s[i] - '0';
            else if (s[i] >= 'A' && s[i] <= 'Z')
                x = s[i] - 'A' + 10;
            else if (s[i] >= 'a' && s[i] <= 'z')
                x = s[i] - 'a' + 36;
            in.push_back(x);
        }
        // 高精度的常规做法是把最高位放在 vector 最末尾
        reverse(in.begin(), in.end());
        // 直到处理完毕，商 0
        while (in.size()) {
            // 表示进位
            int r = 0;
            // 从最高位开始除
            for (int i = in.size() - 1; i >= 0; i--) {
                int x = r * a + in[i];
                in[i] = x / b, r = x % b;
            }

            // 记录当前结果到 out
            out.push_back(r);

            // 除完之后，删除前导 0
            while (in.size() && in.back() == 0) in.pop_back();
        }
        cout << a << " " << s << endl
             << b << " ";
        for (int i = out.size() - 1; i >= 0; i--) {
            int x = out[i];
            if (x >= 0 && x <= 9)
                cout << char(x + '0');
            else if (x >= 10 && x <= 35)
                cout << char(x - 10 + 'A');
            else
                cout << char(x - 36 + 'a');
        }
        cout << endl
             << endl;
    }
    return 0;
}