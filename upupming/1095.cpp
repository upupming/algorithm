#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <iomanip>
#include <assert.h>

using namespace std;

struct Node {
    string plate;
    int time;
    bool isIn;
} record;

int n, k;
vector<Node> records;
map<string, int> s;
map<string, int> duration;


map<string, int> mp;
set<int> toDel;

bool cmp(const Node& a, const Node& b) {
    return a.time < b.time;
}

int sim_i = 0;
void simu(int hh, int mm, int ss) {
    int c = (hh * 60 + mm) * 60 + ss;
    while (sim_i < n && records[sim_i].time <= c) {
        // cout << records[sim_i].plate << endl;
        if (toDel.count(sim_i)) {
            sim_i++;
            continue;
        }
        if (records[sim_i].isIn) {
            s[records[sim_i].plate] = records[sim_i].time;
            // cout << "IN: " << records[sim_i].plate << endl;
        } else {
            assert(s.count(records[sim_i].plate));
            duration[records[sim_i].plate] += records[sim_i].time - s[records[sim_i].plate];
            s.erase(records[sim_i].plate);
            // cout << "OUT: " << records[sim_i].plate << endl;
            // cout << "duration: " << records[sim_i].plate << " = " << duration[records[sim_i].plate] << endl;;
        }
        sim_i++;
    }
}

int main() {
    cin >> n >> k;
    string tmp;
    int hh, mm, ss;
    for (int i = 0; i < n; i++) {
        cin >> record.plate;
        scanf("%d:%d:%d", &hh, &mm, &ss);
        record.time = (hh * 60 + mm) * 60 + ss;
        cin >> tmp;
        record.isIn = (tmp == "in");

        records.push_back(record);
    }

    sort(records.begin(), records.end(), cmp);
    // 删除没有配对的那些
    // cout << "Sorted: " << endl;
    for (int i = 0; i < n; i++) {
        // int maxDuration = records[i].time;
        // ss = maxDuration % 60;
        // maxDuration /= 60;
        // mm = maxDuration % 60;
        // hh = maxDuration / 60;
        // cout << i << " " << records[i].plate << " " << hh << ":" << mm << ":" << ss << " " << (records[i].isIn ? "in" : "out") << endl;

        // In
        if (records[i].isIn) {
            // 多次 In 取最后一次
            if (mp.count(records[i].plate)) {
                toDel.insert(mp[records[i].plate]);
                mp[records[i].plate] = i;
                // cout << "delete1: " << i << ", " << mp[records[i].plate] << endl;
            } else {
                mp[records[i].plate] = i;
            }
        }
        // Out
        else {
            if (!mp.count(records[i].plate)) {
                toDel.insert(i);
                // cout << "delete2: " << i << endl;
            } else {
                mp.erase(records[i].plate);
            }
        }
    }
    // cout << "To delete: " << endl;
    // for (auto i = toDel.begin(); i != toDel.end(); i++) {
    //     cout << (*i) << " ";
    // }
    // cout << endl;

    while (k--) {
        scanf("%d:%d:%d", &hh, &mm, &ss);
        simu(hh, mm, ss);

        cout << s.size() << endl;
    }

    simu(24, 0, 0);
    int maxDuration = 0;
    // 注意 map 是按照 key 排序，而不是 value！！！
    for (auto it = duration.begin(); it != duration.end(); it++) {
        maxDuration = max(maxDuration, it->second);
    }
    int cnt = 0;
    for (auto it = duration.begin(); it != duration.end(); it++) {
        if (it->second == maxDuration) {
            if (cnt > 0) {
                cout << " ";
            }
            cnt++;
            cout << it->first;
        }
    }
    ss = maxDuration % 60;
    maxDuration /= 60;
    mm = maxDuration % 60;
    hh = maxDuration / 60;
    cout << setfill('0') << " " << setw(2) << hh << ":" << setw(2) << mm << ":" << setw(2) << ss << endl;

    return 0;
}