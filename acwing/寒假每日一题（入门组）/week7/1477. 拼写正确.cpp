#include <iostream>
using namespace std;

string nums[] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};
string s, t;
int ans;
int main() {
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        ans += s[i] - '0';
    }
    while (ans) {
        int r = ans % 10;
        t = nums[r] + " " + t;
        ans /= 10;
    }
    cout << (t == "" ? "zero" : t) << endl;
}