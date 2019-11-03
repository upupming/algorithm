#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

struct Student {
    string id;
    int c, m, e, a;
} student;

vector<Student> students;
int n, m;
string query;
map<string, int> rnk;
map<string, char> rnkBy;

int cmp0(const Student& a, const Student& b) { return a.a > b.a; }
int cmp1(const Student& a, const Student& b) { return a.c > b.c; }
int cmp2(const Student& a, const Student& b) { return a.m > b.m; }
int cmp3(const Student& a, const Student& b) { return a.e > b.e; }
typedef int (*cmpType) (const Student&, const Student&);

cmpType cmpAll[] = { cmp0, cmp1, cmp2, cmp3 };
char by[] = "ACME";

int main() {
    students.erase()
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> student.id >> student.c >> student.m >> student.e;
        // 四舍五入
        student.a = (student.c + student.m + student.e) / 3.0 + 0.5;
        students.push_back(student);
    }

    // 注意多人排名相等的情况！！！

    sort(students.begin(), students.end(), cmp0);
    for (int i = 0; i < n; i++) {
        int tmp = i;
        while (tmp > 0 && students[tmp - 1].a == students[tmp].a) tmp--;
        // 可以不用map，直接使用一个很长的数组将学号（学号都是数字）索引到students的下标
        rnk[students[i].id] = tmp + 1;
        rnkBy[students[i].id] = by[0];
    }
    // 要是将 c, m, e 改为数组索引，代码更简洁
    for (int i = 1; i <=3; i++) {
        sort(students.begin(), students.end(), cmpAll[i]);
        for (int j = 0; j < n; j++) {
            int tmp = j;
            if (i == 1)
                while (tmp > 0 && students[tmp - 1].c == students[tmp].c) tmp--;
            if (i == 2)
                while (tmp > 0 && students[tmp - 1].m == students[tmp].m) tmp--;
            if (i == 3)
                while (tmp > 0 && students[tmp - 1].e == students[tmp].e) tmp--;
            if (tmp + 1 < rnk[students[j].id]) {
                rnk[students[j].id] = tmp + 1;
                rnkBy[students[j].id] = by[i];
            }
        }
    }

    while (m--) {
        cin >> query;
        if (rnk.count(query)) {
            cout << rnk[query] << " " << rnkBy[query] << endl;
        } else cout << "N/A" << endl;
        // cout << (rnk.count(query) ? rnk[query] + " " + rnkBy[query] : "N/A") << endl;
    }
    return 0;
}