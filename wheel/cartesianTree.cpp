// https://www.geeksforgeeks.org/cartesian-tree/
// RMQ 相关算法

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int data = 0) : data(data), left(nullptr), right(nullptr) {}
};

void printInOrder(Node* node) {
    if (node == NULL)
        return;
    printInOrder(node->left);
    cout << node->data << " ";
    printInOrder(node->right);
}

Node* insertNodeIntoCartesianTree(Node* root, int val) {
    Node* node = new Node(val);
    if (root == nullptr)
        root = node;
    else {
        Node *last = nullptr, *cur = root;
        // 没有考虑有相等值的情况
        while (cur->data > val && cur->right) {
            last = cur;
            cur = cur->right;
        }
        // Case 1: 将 cur 作为 val 的左子树
        if (cur->data < val) {
            if (last)
                last->right = node;
            else {
                root = node;
            }
            node->left = cur;
        }
        // Case 2: 将 val 作为叶子节点
        else
            cur->right = node;
    }

    return root;
}

Node* buildCartesianTree(const vector<int>& arr) {
    Node* root = nullptr;
    for (auto val : arr)
        root = insertNodeIntoCartesianTree(root, val);
    return root;
}

int main() {
    /* Assume that inorder traversal of following tree
       is given
         40
       /   \
      10     30
     /         \
    5          28 */

    vector<int> arr{5, 10, 40, 30, 28};

    Node* root = buildCartesianTree(arr);

    /* Let us test the built tree by printing Inorder
       traversal */
    printf("Inorder traversal of the constructed tree : \n");
    printInOrder(root);
    cout << endl;

    return (0);
}