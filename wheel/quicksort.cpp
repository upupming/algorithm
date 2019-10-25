#include <iostream>

using namespace std;

// https://www.geeksforgeeks.org/quick-sort/
// https://www.youtube.com/watch?v=MZaf_9IZCrc
int partition(int *a, int low, int high) {
    int pivot = a[high];
    // 记住 i 及其左侧的元素永远都小于 pivot
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i+1], a[high]);
    return i + 1;
}

void quicksort(int *a, int low, int high) {
    if (low < high) {
        int i = partition(a, low, high);
        quicksort(a, low, i - 1);
        quicksort(a, i + 1, high);
    }
}

int a[10] = { 1, 3, 5, 9, 7, 3, 4, 6, 8, 2};

void print() {
    for (int i = 0; i < 10; i++) {
        if (i > 0) cout << " ";
        cout << a[i];
    }
    cout << endl;
}

int main() {
    quicksort(a, 0, 9);
    print();
    return 0;
}