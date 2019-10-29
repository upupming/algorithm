#include <iostream>

using namespace std;

int n, m;
string name[1005], password[1005], orig = "10lO", subs = "@%Lo";
bool modified[1005];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> name[i] >> password[i];
        for (int j = 0; j < password[i].length(); j++) {
            for (int k = 0; k < orig.length(); k++) {
                if (password[i][j] == orig[k]) {
                    modified[i] = true;
                    password[i][j] = subs[k];
                }
            }
        }
        if (modified[i]) m++;
    }
    if (m == 0) {
        if (n == 1) cout << "There is 1 account and no account is modified" << endl;
        else cout << "There are " << n << " accounts and no account is modified" << endl;
    } else {
        cout << m << endl;
        for (int i = 0; i < n; i++) {
            if (modified[i]) {
                cout << name[i] << " " << password[i] << endl;
            }
        }
    }
    return 0;
}