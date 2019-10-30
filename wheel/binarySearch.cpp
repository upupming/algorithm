#include <iostream>

using namespace std;

int binarySearch(int a[], int low, int high, int val) {
    if (low > high) return -1;
    int mid = (low + high) / 2;
    if (a[mid] == val) return mid;
    else if (a[mid] < val) return binarySearch(a, mid + 1, high, val);
    else return binarySearch(a, low, mid - 1, val);
}
int binarySearchLoop(int a[], int low, int high, int val) {
    while (low <= high) {
        int mid = (low + high) / 2;
        if (a[mid] == val) return mid;
        else if (a[mid] < val) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int binarySearchLowerBound(int a[], int low, int high, int val) {
    // a = 0, 1, 2, 2, 4
    // low = 0, high = 4, val = 2
    int i = high + 1;
    while (low <= high) {
        int mid = (low + high) / 2; // mid = 2
        // printf("%d %d %d %d\n", low, high, a[mid], val);
        // 要找第一个 >= val 的位置，所以不考虑 < val 的前半段
        if (a[mid] < val) {
            low = mid + 1;
        }
        // 虽然 a[mid] 满足 >= 条件，但是可能不是最小的那个，需要多次更新
        else { // a[2] == 2
            i = mid; // i = 2
            high = mid - 1; // high = 1
        }
    }
    return i;
}

int binarySearchUpperBound(int a[], int low, int high, int val) {
    // a = 0, 1, 2, 2, 4
    // low = 0, high = 4, val = 2
    int i = high + 1;
    while (low <= high) {
        int mid = (low + high) / 2; // mid = 2; mid = 3; mid = 4
        // 要找第一个 > val 的位置，所以不考虑 <= val 的前半段
        if (a[mid] <= val) { // a[2] == 2; a[3] == 2
            low = mid + 1; // low = 3; low = 4
        }
        // 虽然 a[mid] 满足 > 条件，但是可能不是最小的那个，需要多次更新
        else {
            i = mid; // i = 4
            high = mid - 1; // high = 3
        }
    }
    return i;
}

int main() {
    int a[11] = {  -1, 0, 2, 2, 5, 6, 7, 10, 34, 34, 78 };
    int b[11] = {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    int test[7] = { -1, 78, 2, -2, 34, 79, 1 };
    for (int i = 0; i < 7; i++) {
        printf("a: %d, %d\n", test[i], binarySearchLoop(a, 0, 10, test[i]));
    }
    for (int i = 0; i < 7; i++) {
        printf("b: %d, %d\n", test[i], binarySearchLoop(b, 0, 10, test[i]));
    }

    for (int i = 0; i < 7; i++) {
        printf("a lower: %d, %d\n", test[i], binarySearchLowerBound(a, 0, 10, test[i]));
    }
    for (int i = 0; i < 7; i++) {
        printf("a uppper: %d, %d\n", test[i], binarySearchUpperBound(a, 0, 10, test[i]));
    }

    printf("b lower: %d, %d\n", 1, binarySearchLowerBound(b, 0, 10, 1));
    printf("b uppper: %d, %d\n", 1, binarySearchUpperBound(b, 0, 10, 1));

    return 0;
}