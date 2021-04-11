#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    int prev, next;
} node[510];

void remove(int p) {
    node[node[p].prev].next = node[p].next;
    node[node[p].next].prev = node[p].prev;
}

class Solution {
   public:
    int findTheWinner(int n, int k) {
        for (int i = 1; i <= n; i++) {
            node[i].val = i;
        }
        // 建立链表连接，node[0] 和 node[n+1] 表示 head 和 tail
        for (int i = 1; i <= n - 1; i++) {
            node[i].next = i + 1;
            node[i + 1].prev = i;
        }
        node[1].prev = n, node[n].next = 1;

        int cnt = 0, cur = 1;
        while (cnt != n - 1) {
            for (int i = 0; i < k - 1; i++) cur = node[cur].next;
            int next = node[cur].next;
            // cout << cur << endl;
            remove(cur), cnt++;
            cur = next;
        }
        return cur;
    }
};
