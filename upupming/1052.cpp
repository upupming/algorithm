/**
1. 统计所有用到的数的下标
2. 将用到的数进行排序
3. 对有序下标分配 next 值
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int address[100005], key[100005], nxt[100005], pos[100005];
int n, head;
// pos 记录 node 的下标，used 记录真正在链表中的下标
vector<int> used;
int cmp(int a, int b) { return key[a] < key[b]; }
int main() {
    scanf("%d%d", &n, &head);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &address[i], &key[i], &nxt[i]);
        pos[address[i]] = i;
    }
    int current = head;
    while (current != -1) {
        used.push_back(pos[current]);
        current = nxt[pos[current]];
    }
    if (used.size() == 0) {
        printf("0 -1\n");
        return 0;    
    }
    // sort 空数组会发生 segmentation fault：begin()+1 is past the end()
    sort(used.begin(), used.end(), cmp);
    printf("%d %05d\n", used.size(), address[used[0]]);
    // 注意 used 为空的情况！！！不要把第二个 printf 放在外部
    int i;
    for (i = 0; i < used.size(); i++) {
        if (i != used.size() - 1)
            printf("%05d %d %05d\n", address[used[i]], key[used[i]], address[used[i+1]]);
        else
            printf("%05d %d %d\n", address[used[i]], key[used[i]], -1);
    }
    return 0;
}