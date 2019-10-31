#include <iostream>

using namespace std;

int n, m, heap[1005];
bool flag;

bool isHeap(int i, bool maxHeap, string& post) {
    if (i >= n) return true;
    // cout << i << ", " << heap[i] << endl;
    int left = 2 * i + 1, right = 2 * i + 2;
    if (maxHeap) {
        bool a = isHeap(left, maxHeap, post);
        bool b = isHeap(right, maxHeap, post);
        post += " " + to_string(heap[i]);    
        if (left < n && heap[i] < heap[left]) return false;
        if (right < n && heap[i] < heap[right]) return false;
        return a && b;
    }
    else {
        bool a = isHeap(left, maxHeap, post);
        bool b = isHeap(right, maxHeap, post);
        post += " " + to_string(heap[i]);
        if (left < n && heap[i] > heap[left]) return false;
        if (right < n && heap[i] > heap[right]) return false;
        return a && b;
    }
}

int main() {
    cin >> m >> n;
    while (m--) {
        for (int i = 0; i < n; i++) cin >> heap[i];
        string s, t;
        if (isHeap(0, true, s)) cout << "Max Heap" << endl << s.substr(1) << endl;
        else if (isHeap(0, false, t)) cout << "Min Heap" << endl << t.substr(1) << endl;
        else cout << "Not Heap" << endl << t.substr(1) << endl;
    }
    return 0;
}