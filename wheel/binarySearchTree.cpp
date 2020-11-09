// https://geeksforgeeks.org/construct-bst-from-given-preorder-traversa/
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

void printInOrder(Node* node) {
    if (node == NULL)
        return;
    printInOrder(node->left);
    cout << node->data << " ";
    printInOrder(node->right);
}

// TODO: method 1 + monotonic stack is also O(n) time complexity

// O(n) time complexity
Node* constructBinarySearchTree(const vector<int>& pre, int& curPreIndex, int min = INT_MIN, int max = INT_MAX) {
    Node* root = nullptr;
    if (curPreIndex >= pre.size()) return root;

    int curVal = pre[curPreIndex];
    // 暂时不处理等于情况
    if (curVal > min && curVal < max) {
        curPreIndex++;
        root = new Node;
        root->data = curVal;
        // 左子树需要小于当前值
        root->left = constructBinarySearchTree(pre, curPreIndex, min, curVal);
        // 右子树需要大于当前值
        root->right = constructBinarySearchTree(pre, curPreIndex, curVal, max);
    }
    return root;
}

Node* constructBinarySearchTree(vector<int> pre) {
    int curPreIndex = 0;
    return constructBinarySearchTree(pre, curPreIndex);
}

int main() {
    /**
     10
   /   \
  5     40
 /  \      \
1    7      50
*/
    vector<int> pre{10, 5, 1, 7, 40, 50};

    // Function call
    Node* root = constructBinarySearchTree(pre);

    cout << "Inorder traversal of the constructed tree: \n";
    printInOrder(root);
    cout << endl;

    return 0;
}