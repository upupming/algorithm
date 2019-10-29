#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct People {
    string name;
    int age, netWorth;
} people;

int cmp(People a, People b) {
    if (a.netWorth == b.netWorth) {
        if (a.age == b.age) {
            return a.name < b.name;
        } else return a.age < b.age;
    } else return a.netWorth > b.netWorth;
}

int n, k, amin, amax, maxout;
vector<People> peoples;
int main() {
    // 此题直接使用 cout 会超时
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> people.name >> people.age >> people.netWorth;
        peoples.push_back(people);
    }
    sort(peoples.begin(), peoples.end(), cmp);
    for (int i = 1; i <= k; i++) {
        cin >> maxout >> amin >> amax;
        // printf("Case #%d:\n", i);
        cout << "Case #" << i << ":" << endl;
        
        int cnt = 0;
        // 提前结束，否则超时
        for (int j = 0; j < peoples.size() && cnt < maxout; j++) {
            if (peoples[j].age >= amin && peoples[j].age <= amax) {
                cout << peoples[j].name << " "
                << peoples[j].age << " "
                << peoples[j].netWorth << endl;    
                cnt++;
            }
        }
        if (cnt == 0) cout << "None" << endl;
    }
}
