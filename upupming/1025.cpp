#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Stu {
    string regNum;
    int finalRank, localNum, localRank, score;
} stu;

vector<Stu> students;
int n, k;

int cmp(const Stu& a, const Stu& b) { return a.score > b.score; }
int cmp1(const Stu& a, const Stu& b) { 
    if (a.finalRank != b.finalRank) {
        return a.finalRank < b.finalRank;
    } else return a.regNum < b.regNum;
}

int main() {
    cin >> n;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        cin >> k;
        stu.localNum = i;
        for (int j = 0; j < k; j++) {
            cin >> stu.regNum >> stu.score;
            students.push_back(stu);
        }
        // 当场排名
        sort(students.begin() + cnt, students.end(), cmp);
        for (int j = cnt; j < students.size(); j++) {
            if (j - 1 >= 0 && students[j - 1].score == students[j].score) {
                students[j].localRank = students[j - 1].localRank;
            } else students[j].localRank = j + 1 - cnt;
        }
        cnt += k;
    }
    // 总排名
    sort(students.begin(), students.end(), cmp);
    for (int j = 0; j < students.size(); j++) {
        if (j - 1 >= 0 && students[j - 1].score == students[j].score) {
            students[j].finalRank = students[j - 1].finalRank;
        } else students[j].finalRank = j + 1;
    }

    sort(students.begin(), students.end(), cmp1);
    cout << students.size() << endl;
    for (int i = 0; i < students.size(); i++) {
        cout << students[i].regNum << " " << students[i].finalRank
            << " " << students[i].localNum 
            << " " << students[i].localRank << endl;
    }
    return 0;
}