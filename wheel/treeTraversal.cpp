#include <iostream>
#include <stack>

using namespace std;

struct Node {
    int data;
    struct Node *left, *right;
    Node (int data) {
        this->data = data;
        left = right = nullptr;
    }
};

string preRecur(Node *root) {
    if (root != nullptr) {
        return 
            to_string(root->data) + " " +
            preRecur(root->left) +
            preRecur(root->right);
    }
    return "";
}
string pre(Node *root) {
    string res;
    stack<Node*> s;
    Node *current = root;
    while (current) {
        while (current) {
            res += to_string(current->data) + " ";
            s.push(current);
            current = current->left;
        }
        // 一直弹出直到有右子树的情况
        while (!current && !s.empty()) {
            // 左子树完毕，开始遍历右子树
            current = s.top();
            s.pop();
            current = current->right;
        }
    }
    return res;
}
string inRecur(Node *root) {
    if (root != nullptr) {
        return
            inRecur(root->left) +
            to_string(root->data) + " " +
            inRecur(root->right);
    }
    return "";
}
string in(Node *root) {
    string res;
    stack<Node*> s;
    Node *current = root;
    while (current) {
        while (current) {
            s.push(current);
            current = current->left;
        }
        // 一直弹出直到有右子树的情况
        while (!current && !s.empty()) {
            // 左子树完毕，开始遍历右子树
            current = s.top();
            // 跟中序一样，只是打印变成了在从栈中弹出时才打印
            res += to_string(current->data) + " ";
            s.pop();
            current = current->right;
        }
    }
    return res;
}

string postRecur(Node *root) {
    if (root != nullptr) {
        return 
            postRecur(root->left) +
            postRecur(root->right) +
            to_string(root->data) + " ";
    }
    return "";
}
string post(Node *root) {
    string res;
    stack<Node*> s;
    Node *current = root, *lastVisit = root;
    while (current || !s.empty()) {
        while (current) {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        // 右子树已访问完毕
        if (!current->right || current->right == lastVisit) {
            res += to_string(current->data) + " ";
            s.pop();
            lastVisit = current;
            // 置为 NULL 继续寻找上一个父亲
            current = nullptr;
        } else {
            // 不出栈，而是继续访问右子树
            current = current->right;
        }
    }
    return res;
}

/**
     1
    / \ 
   2   3
  /     \
 4       5
  \
   6
  / \
 7   8
*/
Node *getTree() {
    Node *root = new Node(1), *current = root;
    current->left = new Node(2), current->right = new Node(3);
    current = current->left;
    current->left = new Node(4);
    current = current->left;
    current->right = new Node(6);
    current = current->right;
    current->left = new Node(7), current->right = new Node(8);
    
    current = root->right;
    current->right = new Node(5);

    return root;
}

int main() {
    Node *root = getTree();
    cout << "Recursive: " << endl;
    cout << "Preorder: " << preRecur(root) << endl;
    cout << "Inorder: " << inRecur(root) << endl;
    cout << "Postorder: " << postRecur(root) << endl;

    cout << "Non-Recursive:" << endl;
    cout << "Preorder: " << pre(root) << endl;
    cout << "Inorder: " << in(root) << endl;
    cout << "Postorder: " << post(root) << endl;
    return 0;
}