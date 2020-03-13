// https://youtu.be/mjZpZ_wcYFg
#include <iostream>

using namespace std;

// abc -> 1a1b1c
// aabbbcc -> 2a3b2c

string solve(string str) {
    string ans = "";
    // 算上 str[0]，有一个了
    int acc = 1;
    // 双指针
    for (int i = 0; i < str.length(); i++) {
        // 测试 str[i+1] 能不能累计
        if (i + 1 < str.length() && str[i] == str[i + 1]) {
            acc++;
        } else {
            ans += to_string(acc);
            ans += str[i];
            acc = 1;
        }
    }
    cout << ans << endl;
    return ans;
}

string unsolve(string str) {
    string ans;
    for (int i = 0; i + 1 < str.length(); i += 2) {
        int num = str[i] - '0';
        ans += string(num, str[i + 1]);
    }
    cout << ans << endl;
    return ans;
}

int main() {
    solve("abc");
    solve("aabbbcc");
    solve("");

    unsolve(solve("abc"));
    unsolve(solve("aabbbcc"));
    unsolve(solve(""));
    return 0;
}