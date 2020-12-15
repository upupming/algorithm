// 二叉堆模板，书上下标从 1 开始索引，这个例子是最大堆
int heap[N], n;
// 向上调整
void up(int p) {
    while (p > 1) {
        if (heap[p] > heap[p / 2]) {
            swap(heap[p], heap[p / 2]);
            p /= 2;
        } else
            break;
    }
}
void insert(int val) {
    heap[++n] = val;
    up(n);
}
int getTop() { return heap[1]; }
// 向下调整
void down(int p) {
    // 左子节点
    int s = 2 * p;
    while (s <= n) {
        // 左右子节点中取较大者
        if (s < n && heap[s] < heap[s + 1]) s++;
        if (heap[p] < heap[s]) {
            swap(heap[p], heap[s]);
            p = s, s = 2 * p;
        } else
            break;
    }
}
void extract() {
    heap[1] = heap[n--];
    down(1);
}
void remove(int k) {
    heap[k] = heap[n--];
    up(k), down(k);
}