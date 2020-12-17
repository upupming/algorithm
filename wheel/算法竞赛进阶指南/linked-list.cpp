// 数组模拟链表
struct Node {
    int value;
    int prev, next;
} node[SIZE];
int head, tail, tot;

int initialize() {
    tot = 2;
    head = 1, tail = 2;
    node[head].next = tail;
    node[tail].prev = head;
}

int insert(int p, int value) {
    q = ++tot;
    node[q].value = value;
    node[node[p].next].prev = q;
    node[q].next = node[p].next;
    node[p].next = q;
    node[q].prev = p;
}

void remove(int p) {
    node[node[p].prev].next = node[p].next;
    node[node[p].next].prev = node[p].prev;
}