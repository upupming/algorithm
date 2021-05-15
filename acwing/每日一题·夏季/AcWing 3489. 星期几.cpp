#include <iostream>
using namespace std;

bool isLeap(int x) {
    return (x % 4 == 0 && x % 100 != 0) || x % 400 == 0;
}

int d, y;
string m;
string a[12] = {
    "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
int days[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
string v[7] = {
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
int main() {
    while (cin >> d >> m >> y) {
        int mInt = 0;
        for (; mInt < 12; mInt++) {
            if (a[mInt] == m) {
                break;
            }
        }

        int cnt = 0;
        for (int i = 1; i <= y - 1; i++) {
            cnt += 365 + isLeap(i);
        }
        for (int i = 0; i <= mInt - 1; i++) {
            cnt += days[i];
            if (i == 1 && isLeap(y)) cnt += 1;
        }
        cnt += d;

        cout << v[(cnt + 6) % 7] << endl;
    }

    return 0;
}
