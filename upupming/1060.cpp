#include <iostream>

using namespace std;

int n;
string a, b;

void print(string& a, int ka) {
    cout << "0.";
    for (int i = 0; i < n; i++) {
        char ai;
        if (i >= a.length()) ai = '0';
        else ai = a[i];
        cout << ai;
    }
    cout << "*10^" << ka;
}

int ka, kb;

void process(string& a, int& ka) {
    int i;
    for (i = 0; i < a.length() && a[i] == '0'; i++);
    // 删除前导 0
    a.erase(0, i);

    ka = a.find('.');
    if (ka == -1) ka = a.length();
    if (ka == 0) {
        int i;
        for (i = 1; i < a.length() && a[i] == '0'; i++);
        // 删除前导 0
        a.erase(0, i);
        ka = -(i - 1);
        if (a.length() == 0) ka = 0;
    }
    else a = a.erase(ka, 1);

    // cout << ka << " " << a << endl << endl;
}

int main() {
    cin >> n >> a >> b;
    process(a, ka);
    process(b, kb);
    bool flag = true;
    if (ka != kb) flag = false;
    else {
        for (int i = 0; i < n; i++) {
            char ai, bi;
            if (i >= a.length()) ai = '0';
            else ai = a[i];
            if (i >= b.length()) bi = '0';
            else bi = b[i];
            if (ai != bi) {
                flag = false;
                break;
            }
        }
    }
    if (flag) {
        cout << "YES ";
        print(a, ka);
        cout << endl;
    } else {
        cout << "NO ";
        print(a, ka);
        cout << " ";
        print(b, kb);
        cout << endl;
    }
    return 0;
}

// 4 0.12301 0.12302
// 4 0.012301 0.012302 d[1]>0 unless the number is 0!!!
// 8 12300 12300.1
// 4 01.0 1.001
// 4 0.0 00.000
// 2 0.1 0.1