/*
除了 K 以外，其他牌具有对称性，但是为了进行下标索引，还是需要转为数字

支持放在堆上面，又要从底下抽取一张，可以用 deque 来存储牌
仔细分析一下，放在上面这个过程只需要计数即可，不必真正的放入，可以直接用 vector 就行
模拟一下整个过程即可
*/
#include <iostream>
#include <map>
#include <vector>
using namespace std;

map<char, int> m{{'A', 1}, {'0', 10}, {'J', 11}, {'Q', 12}, {'K', 13}};
vector<int> d[14];
// 统计正面朝上的数的个数
int cnt[14];
int main() {
    char ch;
    int x;
    for (int i = 1; i <= 13; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> ch;
            x = ch - '0';
            if (x >= 2 && x <= 9)
                d[i].push_back(x);
            else
                d[i].push_back(m[ch]);
        }
    }
    for (int i = 0; i < 4; i++) {
        x = d[13][i];
        while (x != 13) {
            cnt[x]++;
            int y = d[x].back();
            d[x].pop_back();
            x = y;
        }
    }
    int ans = 0;
    for (int i = 1; i <= 12; i++) {
        ans += (cnt[i] == 4);
    }
    cout << ans << endl;
    return 0;
}