#include <iostream>
#include <set>
#include <vector>
using namespace std;

int n;
set<int> s;
vector<int> chosen;

void print() {
    for (int i = 0; i < chosen.size(); i++) {
        if (i > 0)
            cout << " ";
        cout << chosen[i];
    }
    cout << endl;
}

void dfs() {
    if (chosen.size() == n) print();
    for (auto it = s.begin(); it != s.end(); it++) {
        auto t = *it;
        chosen.push_back(t);
        s.erase(t);
        dfs();
        chosen.pop_back();
        it = s.insert(t).first;
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) s.insert(i);
    dfs();
    return 0;
}